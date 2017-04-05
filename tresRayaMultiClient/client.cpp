 /* Client code in C */
 /* <n_bits||sizenombre||estado||data1||data2||data3||data4||nombre> 
<n_bits||sizenombre||0||size tablero||ficha||0||0||nombre>  Crear juego
<n_bits||sizenombre||1||0||ficha||0||0||nombre> Conectarse
<n_bits||6||2||size_tablero||mi turno||turno||0||server> Iniciar juego
<n_bits||sizenombre||3||x||y||turno||ficha||nombre> Mover
<n_bits||sizenombre||4||x||y||0||ficha||nombre>  Gane
*/
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include "protocolo.h"
  int main(void)
  {
    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int n;
    /*Protocolo y juego */
    string proc,nombre;
    datosProtocol protocol;
    Game juego;
    char ficha;
    int turno;


    char buffer[256]; //Para almacenar lo que se escribe
 	char message[30];
    if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1100);
    Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);
 
    if (0 > Res)
    {
      perror("error: first parameter is not a valid address family");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
      perror("char string (second parameter does not contain valid ipaddress");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    /*Iniciando el juego*/
    int opcion = 0;
    cout<<"Elija una opcion\n 1)Crear partida\n 2)Conectarse a una partida\n"<<endl;
    cin >> opcion;
    if (opcion == 1)
    {
    	proc = generarProtocolo(0,nombre,ficha);
	    cout << "Protocolo enviado: "<<proc <<endl;
	    bzero(message,30);
	    strcpy(message, proc.c_str()); //copiandolo al buffer
	    procesarProtocolo(proc,protocol);
	    cout<< "here" <<  protocol.estado<<endl;
	    n = send(SocketFD,message,30,0);
    }

    if (opcion == 2)
    {
    	proc = generarProtocolo(1,nombre,ficha);
	    cout << "Protocolo enviado: "<<proc <<endl;
	    bzero(message,30);
	    strcpy(message, proc.c_str()); //copiandolo al buffer
	    procesarProtocolo(proc,protocol);
	    cout<< "here" <<  protocol.estado<<endl;
	    n = send(SocketFD,message,30,0);
    }

    printf("Esperando confirmacion.....\n");
    bzero(buffer,256);
    n = read(SocketFD,buffer,255);
    if (n < 0) perror("ERROR reading from socket");
//        printf("Chat: [%s]\n",buffer);
    proc = procesarBuffer (buffer);
    procesarProtocolo(proc,protocol);
    cout<<"Protocolo recibido :"<<proc<<endl;
    turno = protocol.data2; //Saber cual es mi turno
    /* perform read write operations ... */

    /*Inicializando el juego */
    Game temp(str_to_int(protocol.dato1),ficha);
    juego = temp;
    juego.print();

    /*juego cliente - servidor*/
    jugar(SocketFD,juego,n,protocol,turno,ficha,nombre);
/*
 	do
 	{
 		 printf("Esperando mensaje.....\n");
 		 bzero(buffer,256);
     	n = read(SocketFD,buffer,255);
     	if (n < 0) perror("ERROR reading from socket");
     	printf("Chat: [%s]\n",buffer);
     	if (buffer[0]=='c' && buffer[1]=='h' && buffer[2]=='a' && buffer[3]=='u') break;
     	bzero(message,18);
     	printf("Mensaje: ");
     	int i=0;
     	while((message[i++]=getchar())!='\n');
     	message[i-1]=0;
     	n = write(SocketFD,message,18);
     	if (n < 0) perror("ERROR writing to socket");
 	} while (message[0]!='c' && message[1]!='h' && message[2]!='a' && message[3]!='u');*/
    

    printf("Juego finalizado\n");
    shutdown(SocketFD, SHUT_RDWR);
    close(SocketFD);
    return 0;
  }
