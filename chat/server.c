  /* Server code in C */
 
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
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    char buffer[256];
    char message[18];
    int n;
 
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
  
    for(;;)
    {
      int ConnectFD = accept(SocketFD, NULL, NULL);
 
      if(0 > ConnectFD)
      {
        perror("error accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
 
      do
      {
        printf("Esperando mensaje.....\n");
        bzero(buffer,256);
        n = read(ConnectFD,buffer,255);
        if (n < 0) perror("ERROR reading from socket");
        printf("Chat: [%s]\n",buffer);
        if (buffer[0]=='c' && buffer[1]=='h' && buffer[2]=='a' && buffer[3]=='u') break;
        bzero(message,18);
        printf("Mensaje: ");
        scanf("%s",message);
        n = write(ConnectFD,message,18);
        if (n < 0) perror("ERROR writing to socket");
      } while (message[0]!='c' && message[1]!='h' && message[2]!='a' && message[3]!='u');

      printf("Chat finalizado\n");
     /* perform read write operations ... */
 
      shutdown(ConnectFD, SHUT_RDWR);
 
      close(ConnectFD);
    }
 
    close(SocketFD);
    return 0;
  }
