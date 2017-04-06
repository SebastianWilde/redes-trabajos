  /* Server code in C */
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <map>
#include "protocolo.h"
#include <pthread.h>

void *task1(void * rank);
vector <int> sockets; //para almacenar los sockets
map <string,int> datos;
int tempTurno = 1;// para asignar el numero de turno
/*Variables globales*/
int turno = 0; //a que jugador le pertenece el turno
int sizeTablero = 0;
int cantidadJugadores = 0;
string nombreServidor = "server";
volatile bool mensajePendiente= 0;  //mensaje pendiente para enviar
pthread_mutex_t mutex;

/*Protocolo */
string proc;
datosProtocol protocol;

  int main(void)
  {
    /*Threads*/
    pthread_t threadA[4];

    struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

 
    if(-1 == SocketFD)
    {
      perror("can not create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1100);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;
 
    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("error bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if(-1 == listen(SocketFD, 10))
    {
      perror("error listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    int ConnectFD;
    int nThreads = 0;
    for(;;)
    {
    	while (nThreads < 4)
    	{
    		ConnectFD = accept(SocketFD, NULL, NULL);
		    if(0 > ConnectFD)
		    {
		        perror("error accept failed");
		        close(SocketFD);
		        exit(EXIT_FAILURE);
		    }

		    cout << "Connection successful" << endl;
	        pthread_create(&threadA[nThreads], NULL, task1, (void *)nThreads);
	        sockets.push_back(ConnectFD);
        	nThreads++;
    	}
    	for(int i = 0; i < 4; i++)
		{
		    pthread_join(threadA[i], NULL);
		}
      	printf("Juego finalizado\n");
     	/* perform read write operations ... */
      	/*shutdown(ConnectFD, SHUT_RDWR);
      	close(ConnectFD);*/
    }
 
    close(SocketFD);
    return 0;
  }

void *task1 (void *rank)
{
    int my_rank=(int) rank;
    string miProc,clnName;
    datosProtocol miProtocol;
    char clnFicha;
    char buffer[256];
    char message[40];
    int n,aux = 0;
    /*Al iniciar*/
    bzero(buffer,256);
   	n = read(sockets[my_rank],buffer,255);
    miProc = procesarBuffer (buffer);
    procesarProtocolo(miProc,miProtocol);
    clnName = miProtocol.nombre;
   	clnFicha = str_to_char(miProtocol.dato2);
 
   	//pthread_mutex_lock(&mutex);
   	datos[clnName] = tempTurno;

   	tempTurno++;

   	cantidadJugadores++;
   	//pthread_mutex_lock(&mutex);
   	cout<<"th "<< my_rank<<" protoclo recibido: "<<miProc<<" de "<<clnName<<endl;
    if (miProtocol.estado == 0) //Creacion del juego
    {

    	cout<<"th "<< my_rank<<" Creacion de juego "<<endl;

    	sizeTablero = str_to_int(miProtocol.dato1);
    	/*Preparar lo que va a enviar*/
    	miProc = generarProtocolo(2, nombreServidor, clnFicha);
    	procesarProtocolo(miProc,miProtocol);
    	turno = 1; //inicializa que el primer turno es del jugador que creo la partida
		miProtocol.dato1 = to_string(sizeTablero); //cambio el primer dato del protocolo en cadena
		miProtocol.dato2 = str_to_char(to_string(datos[clnName])); //pongo el turno que le corresponde
		miProtocol.dato3 = str_to_char(to_string(turno)); //en que turno comienza el juego
		miProtocol.generarStringProtocol();
		miProc = miProtocol.protocolo;
    	while (cantidadJugadores!=4);  //mientras no esten todos conectados
    	bzero(message,40);
	    strcpy(message, miProc.c_str()); //copiandolo al buffer
	    cout<< "Thread n "<<my_rank<<" envia " <<  miProtocol.estado<<" a "<<clnName<<" con turno "<<datos[clnName]<<endl;
	    n = send(sockets[my_rank],message,40,0);
    }

    if (miProtocol.estado == 1) //Conectarse a la partida
    {

    	/*Preparar lo que va a enviar*/
    	pthread_mutex_lock(&mutex);
    	cout<<"th "<< my_rank<<"Conectandose al juego"<<endl;
    	pthread_mutex_unlock(&mutex);

    	miProc = generarProtocolo(2, nombreServidor, clnFicha);
    	procesarProtocolo(miProc,miProtocol);
		miProtocol.dato1 = to_string(sizeTablero); //cambio el primer dato del protocolo en cadena
		miProtocol.dato2 = str_to_char(to_string(datos[clnName])); //pongo el turno que le corresponde
		miProtocol.dato3 = str_to_char(to_string(turno)); //en que turno comienza el juego
		miProtocol.generarStringProtocol();
		miProc = miProtocol.protocolo;
    	while (cantidadJugadores!=4);  //mientras no esten todos conectados
    	bzero(message,40);
	    strcpy(message, miProc.c_str()); //copiandolo al buffer
	    cout<< "Thread n "<<my_rank<<" envia " <<  miProtocol.estado<<" a "<<clnName<<" con turno "<<datos[clnName]<<endl;
	    n = send(sockets[my_rank],message,40,0);

    }
    /*Iniciando el juego*/
    /* perform read write operations ... */
    do
    {
    	cout<< "Thread n "<<my_rank<<" listo para recibir "<<endl;
    	bzero(buffer,256);
   		n = read(sockets[my_rank],buffer,255);
    	miProc = procesarBuffer (buffer);
    	procesarProtocolo(miProc,miProtocol);
    	aux = miProtocol.estado;
    	cout<<"th "<< my_rank<<" protoclo recibido: "<<miProc<<" de "<<miProtocol.nombre<<endl;
    	if (aux == 3)
    	{
    		pthread_mutex_lock(&mutex);
    		cout<<"th "<< my_rank<<"Jugando ..."<<endl;
    		turno ++;
    		if (turno > 4) turno = 1;
    		miProtocol.dato3 = to_string(turno); //actulizar el turno
    		miProtocol.generarStringProtocol();
    		miProc = miProtocol.protocolo;
    		bzero(message,40);
			strcpy(message, miProc.c_str()); //copiandolo al buffer
    		int i;
    		cout<<"th "<< my_rank<<" protocolo ..."<<miProc<<endl;
    		for (i = 0; i < 4; i++)
    		{
    			if (i == my_rank) continue;
			    cout<< "Thread n "<<my_rank<<" envia " <<  miProc <<" a "<<i+1<<endl;
			    n = send(sockets[i],message,40,0);
    		}
    		pthread_mutex_unlock(&mutex);
    	}
    	else
    	{  
			strcpy(message, miProc.c_str()); //copiandolo al buffer
			int i;
    		for (i = 0; i < 4; i++)
    		{
    			if (i == my_rank) continue;
			    cout<< "Thread n "<<my_rank<<" envia " <<  miProc <<" a "<< i+1;
			    n = send(sockets[i],message,40,0);
    		}
    	}
    }while (aux != 4);
    shutdown(sockets[my_rank], SHUT_RDWR);
    close(sockets[my_rank]);
}