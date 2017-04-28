/* Client code in C */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<string.h>
#include<string>
#include<iostream>
#include <sstream>
#include<bits/stdc++.h>
using namespace std;
#include"HandleTCPClient.h"

#define MAXPENDING 5    /* Maximum outstanding connection requests */

void *ThreadMain(void *threadArgs);
char echobuffer[RCVBUFSIZE];
Game player_client;
int my_port;
string id;
int p;
string port_string;
void _inicio()
{
    string datos="",p;

    printf("Pieza de juego (X/O)\n");
    cin>>p;
    cout<<"creaando jugador\n";
    Game temp(0,p);
    cout<<"jugador ya creado \n";
    player_client=temp;
}
struct ThreadArgs
{
    int port;                      /* Socket descriptor for client */
};
int main(int argc, char *argv[])
{
    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP
    int n;



    struct ThreadArgs *threadArgs;
    pthread_t threadID;              /* Thread ID from pthread_create() */

    // char echobuffer[256];

    printf("puerto servidor\n");
    scanf("%d",&p);
    stSockAddr.sin_port = htons(p);

    printf("puerto para respuestas\n");
    scanf("%d",&my_port);
    port_string = to_string(my_port);
    if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs)))
            == NULL)
        DieWithError("malloc() failed");
    threadArgs -> port = my_port;
    if (pthread_create(&threadID, NULL, ThreadMain, (void *) threadArgs) != 0)
        DieWithError("pthread_create() failed");


    _inicio();
    while(1)
    {
        string command,parameters;
        cin>>command;
        cin>>parameters;
        parameters+=","+player_client.ficha;
        //header format:
        //tam port,tam command, tam parameters,tam id
        string header;
        header = make_header_send(port_string,command,parameters,id);
        if(command=="login")//header port login (ficha)
        {

            parameters=header+port_string+command+parameters+id;

            connect_and_send(to_string(p),parameters);
        }
        else
        {
            parameters=header+port_string+command+parameters+id;//header port

            if(command =="init")//header port init (nombre tamaño,ficha) id
            {
                connect_and_send(to_string(p),parameters);
            }
            else if(command=="join")//header port join (nombre,ficha) id
            {
                connect_and_send(to_string(p),parameters);
            }
            else if(command=="play")//header port (pos_x,pos_y,ficha) id
            {
                connect_and_send(to_string(p),parameters);
            }
        }
        shutdown(SocketFD, SHUT_RDWR);
        close(SocketFD);
    }
    return 0;
}
//aca proceso envios del servidor
void *ThreadMain(void *threadArgs)
{
    int port;
    char echoBuffer[RCVBUFSIZE];
    /* Guarantees that thread resources are deallocated upon return */
    pthread_detach(pthread_self());

    /* Extract socket file descriptor from argument */
    port = ((struct ThreadArgs *) threadArgs) -> port;
    free(threadArgs);              /* Deallocate memory for argument */

    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */

    unsigned int clntLen;            /* Length of client address data structure */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)

    {
        perror("socket() failed");
        exit(1);
    }
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(port);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)

    {
        perror("bind() failed");
        exit(1);
    }
    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        //  DieWithError("listen() failed");
    {
        perror("listen() failer");
        exit(1);

    }
    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,
                               &clntLen)) < 0)

        {
            perror("accept() failer");
            exit(1);

        }

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        int recvMsgSize=1;                    /* Size of received message */


        recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0);
        if ((recvMsgSize) <= 0)
        {
            printf("error handletcpclient_recv\n");
            //return -2;
        }
        datos_protocol info;
        string status;
        processing_format_protocol_server(status,info,echoBuffer);
        vector<string> datos_p = split(info.parameters,',');
        cout<<"============================================="<<endl;
        cout<<"RESPONSE:"<<endl;
        cout<<"command "<<info.command<<"  --- "<<info.parameters<<endl;
        cout<<"=============================================="<<endl;
        cout<<status<<endl;
        if(status=="err")
        {
            continue;
        }
        if(info.command=="play")//play,x,y,ficha
        {
            int x= str_to_int(datos_p[0]);//primera coordenada a mover
            int y= str_to_int(datos_p[1]);// segunda coordenada a mover
            int is_win;//=str_to_int(datos_p[3]);//verifico si gane
            cout<<"pos "<<x<<" "<<y<<endl;
            cout<<is_win<<" _ "<<endl;
            if(player_client.is_valid(x,y))// es valida la jugada?
            {
                cout<<"posicion a ocupar "<<x<<" "<<y<<endl;
                player_client.board[x][y]=datos_p[2];
                is_win=player_client.is_win(x,y);
            }
            cout<<"flag win "<<is_win<<endl;

            player_client.printboard();// imprimo el teclado
            if(is_win)
            {
                string header;
                string comm = "finish";
                header = make_header_send(port_string,comm,"",id);

                string parameters=header+port_string+comm+id;
                connect_and_send(to_string(p),parameters);

            }
        }
        else if(info.command=="start")
        {

            player_client.bsize=str_to_int(datos_p[0]);
            player_client.restart(player_client.bsize,player_client.ficha);
            player_client.printboard();// imprimo el teclado

        }
        else if(info.command=="finish")
        {

            cout<<"ganador jugador: "<<datos_p[0]<<" ...\n";
            exit(0);
        }
        close(clntSock);
    }

    return (NULL);
}

