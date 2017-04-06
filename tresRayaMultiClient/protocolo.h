/*protocolo.h*/
/* <n_bits||sizenombre||estado||data1||data2||data3||data4||nombre> 
<n_bits||sizenombre||0||size tablero||ficha||0||0||nombre>  Crear juego
<n_bits||sizenombre||1||0||ficha||0||0||nombre> Conectarse
<n_bits||6||2||size_tablero||mi turno||turno inicio||0||server> Iniciar juego
<n_bits||sizenombre||3||x||y||turno||ficha||nombre> Mover
<n_bits||sizenombre||4||x||y||0||ficha||nombre>  Gane
*/

#include <string>
#include <vector>
#include <iterator>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "game.h"
using namespace std;

int str_to_int(string s)
{

    string str = s;
    istringstream buffer(str);
    int value;
    buffer >> value;
    return value;
}

string to_string(int n)
{
	stringstream ss;
	ss<<n;
	return ss.str();
}

char str_to_char(string s)
{
	return s[0];
}

string char_to_string(char a)
{
	string aux="";
	aux+=a;
	return aux;
}
struct datosProtocol {

    int estado, sizeNombre,nBits;
    string dato1,dato2,dato3,dato4,nombre, protocolo;
    datosProtocol(int c,int tamNombre, int nbits,string dat1, string dat2,string dat3, string dat4,string name,string pro)
    {
        sizeNombre = tamNombre;
        nBits = nbits;
        estado=c;
        dato1=dat1;
        dato2=dat2;
        dato3=dat3;
        dato4=dat4;
        nombre=name;
        protocolo=pro;
    }
    datosProtocol() {}

    void generarStringProtocol()
    {
    	protocolo = "<" + to_string(nBits) + "||" + to_string(sizeNombre) + "||" + to_string(estado) + "||" +
    	dato1  + "||" + dato2 + "||" + dato3 + "||" + dato4 + "||" + nombre +">";
    }
};


string generarProtocolo(int estado, string &nombre, char &ficha)
{
	int tamNombre = nombre.size();
	string protocol ="<00||"+ to_string(tamNombre)+"||"+to_string(estado)+"||";
	if (estado == 0) //Crear juego
	{
		int tam;
		cout<<"Ingrese el tam del tamblero :";
		cin>>tam;
		protocol +=to_string(tam)+"||"+ficha+"||0||0||";
	}
	if (estado == 1) //conectarse al juego
	{
		protocol +=string("0||") + ficha + string("||0||0||");
	}

	if (estado == 2) //iniciar juego, esto envia el servidor
	{
		protocol += "0||0||0||0||"; //los datos seran llenados desde el servidor
	}

	if (estado == 3) //moverse
	{
		int x;
		cout<<"Ingrese la posicion x:";
		cin>>x;
		int y;
		cout<<"Ingrese la posicion y:";
		cin>>y;
		protocol +=to_string(x)+"||"+to_string(y)+"||0||"+ficha+"||";
	}

	if (estado == 4) //error, gano, perdio
	{
		protocol +="0||0||0||0||";
	}
	if (estado < 0 || estado > 4)
	{
		cout<<"Error, estado no valido"<<endl;
	}
	protocol+=nombre+">";
	string aux =to_string(protocol.size());
	protocol[1] = aux [0];
	protocol[2] = aux [1];
	return protocol;
}

string procesarBuffer (char *buffer)
{
	string proc="";
	int i;
	for (i=0;i<buffer[1];i++) proc+=buffer[i];
	return proc;
}

void procesarProtocolo (string protoc, datosProtocol &dp)
{
	int bits = (protoc[1] - '0') *10 + (protoc[2] - '0');
	// cout<<"here la conversion "<<bits<<endl;
	dp.nBits = bits;
	dp.sizeNombre = protoc[5] - '0';
	dp.estado = protoc[8] - '0';
	dp.dato1 = protoc[11];
	dp.dato2 = protoc[14];
	dp.dato3 = protoc[17];
	dp.dato4 = protoc[20];

	dp.nombre ="";
	int i;
	for (i=23;protoc[i]!='>';i++)
		dp.nombre+=protoc[i];
	// cout<< "Here :"<<dp.estado<<endl;
	dp.protocolo = protoc;
	return;
}

void jugar(int SocketFD,Game &player_client, int &n, datosProtocol &protocol , int miTurno, char miFicha, string miNombre)
{
	char buffer[256];
	char message[40];
	bzero(buffer,256);
	string proc;
	volatile bool finish = 0;
	do
	{
		if (protocol.estado == 2 && protocol.dato3 == to_string(miTurno))
		{
			proc = generarProtocolo(3, miNombre,miFicha);
			procesarProtocolo(proc,protocol);
			protocol.dato3 = to_string(miTurno); //agregar el turno del que juega al protocolo
			protocol.generarStringProtocol();
			proc = protocol.protocolo;
			bzero(message,40);
	    	strcpy(message, proc.c_str()); //copiandolo al buffer
	    	procesarProtocolo(proc,protocol);
	    	if(!player_client.is_valid(str_to_int(protocol.dato1),str_to_int(protocol.dato2)))
	        {
	                cout<<"coordenada invalida "<<endl;
	                continue;
	        }
	        player_client.board[str_to_int(protocol.dato1)][str_to_int(protocol.dato2)]=miFicha;
	       	player_client.print();
	        if(player_client.is_win(str_to_int(protocol.dato1),str_to_int(protocol.dato2)))
	        {
	            printf("ganas\n");
	            finish = 1;
	            proc = generarProtocolo(4,miNombre,miFicha);
	            strcpy(message, proc.c_str()); //copiandolo al buffer
	    		procesarProtocolo(proc,protocol);
	        }

	        cout << "Protocolo enviado: "<<proc <<endl;
	    	n = send(SocketFD,message,40,0);/* code */
		}
		/*Recibir*/
		else
		{
			printf("Esperando jugada.....\n");
	        bzero(buffer,256);
	        n = read(SocketFD,buffer,255);
	        if (n < 0) perror("ERROR reading from socket");
	//        printf("Chat: [%s]\n",buffer);
	        proc = procesarBuffer (buffer);
	        procesarProtocolo(proc,protocol);
	        cout<<"Protocolo recibido :"<<proc<<endl;
	        cout<<"Protocolo recibido :"<<protocol.estado<<endl;
	        if (protocol.estado == 3)
	        {
	       		if(!player_client.is_valid(str_to_int(protocol.dato1),str_to_int(protocol.dato2)))
		        {
		                cout<<"coordenada invalida "<<endl;
		        }
		        cout<<"Aqui tiene q imprimir "<<protocol.dato1<<" "<<protocol.dato2<<endl;
		        player_client.board[str_to_int(protocol.dato1)][str_to_int(protocol.dato2)]=protocol.dato4;
	        	player_client.print();
	        }
	        if (protocol.estado == 4) 
	        {
	        	player_client.board[str_to_int(protocol.dato1)][str_to_int(protocol.dato2)]=protocol.dato4;
	        	player_client.print();
	        	cout <<"Perdiste "<<endl;
	        	break;
	        }
	        if (protocol.dato3 == to_string(miTurno))
	        {
	        	cout<<"Ready to send sht "<<endl;
	        	/*Enviar*/ 
	        	bzero(message,40);
	        	proc = generarProtocolo(3,miNombre,miFicha);
		    	strcpy(message, proc.c_str()); //copiandolo al buffer
		    	procesarProtocolo(proc,protocol);
		    	if(!player_client.is_valid(str_to_int(protocol.dato1),str_to_int(protocol.dato2)))
		    	{
			        cout<<"coordenada invalida "<<endl;
			        continue;
		    	}
		    	player_client.board[str_to_int(protocol.dato1)][str_to_int(protocol.dato2)]=miFicha;
		    	player_client.print();
		   		if(player_client.is_win(str_to_int(protocol.dato1),str_to_int(protocol.dato2)))
		        {
		            printf("ganas\n");
		            finish = 1;
		            bzero(message,40);
		            proc = generarProtocolo(4,miNombre,miFicha);
		            strcpy(message, proc.c_str()); //copiandolo al buffer
		    		procesarProtocolo(proc,protocol);
		        }
		        cout << "Protocolo enviado: "<<proc <<endl;
	        	n = send(SocketFD,message,40,0);
	        	if (n < 0) perror("ERROR writing to socket");
	        }
	    }
	}while (finish==0);

}
