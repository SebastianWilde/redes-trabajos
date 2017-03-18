 /* Client code in C */
 
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  int main(void)
  {
    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int n;
    char buffer[256]; //Para almacenar lo que se escribe
 	char message[18];
    if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1100);
    Res = inet_pton(AF_INET, "192.168.1.45", &stSockAddr.sin_addr);
 
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
    n = write(SocketFD,"Iniciando chat",18);
    /* perform read write operations ... */
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
 	} while (message[0]!='c' && message[1]!='h' && message[2]!='a' && message[3]!='u');
    printf("Chat finalizado\n");
    shutdown(SocketFD, SHUT_RDWR);
 
    close(SocketFD);
    return 0;
  }
