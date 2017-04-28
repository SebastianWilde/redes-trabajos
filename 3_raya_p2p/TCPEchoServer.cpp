#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <bits/stdc++.h>
#include"HandleTCPClient.h"


using namespace std;
//#include"client_thread.h"

#define MAXPENDING 5    /* Maximum outstanding connection requests */
const int MAX_PLAYER= 2;
//Game player_server(0,"-s");
map<int,string> tabla;
vector<string> jugadores;
map<string,string> users;//puerto - nombre usuario

string tam_tbl;
int cont=0;

void DieWithError(char*);
char echoBuffer[RCVBUFSIZE];

int exist_user(string port_client)
{
    int status=0;
    cout<<"cantidad usuarios exist_user "<<users.size()<<endl;
    cout<<"buscando a "<<port_client<<endl;
    if ( users.find(port_client) == users.end() ) {
        status=1;//no existe
    } else {
        status=0;
    }
    return status;
}

string login(string port_client,int status)
{

    if(status==1) //no existe
    {
        users[port_client]="";
        jugadores.push_back(port_client);
        return "ok";
    }
    return "err";
}
string init_game(string port_client,string nombre,string tabla,int status)
{
    if(status==0)
    {
        tam_tbl=tabla;
        users[port_client]=nombre;
        return "ok";
    }
    return "err";
}
string join(string port_client,string nombre,int status)
{
    if(status==0 && users.size()==MAX_PLAYER)
    {
        users[port_client]=nombre;
        return "ok";
    }
    return "err";
}

void play(string port_client,string comm,string x,string y, string ficha,int &turn,int status)
{
    string stat;
    if(status==0)
    {
        stat="ok";
    }
    else
    {
        stat="err";
    }
    string header;//=comm.size()+","+to_string(stat.size());
    if(users.size()==MAX_PLAYER  && jugadores[turn]==port_client)
    {
        //header +=","+to_string(x.size()+y.size()+ficha.size());
        string parameters= x+","+y+","+ficha;
        header=make_header_response(comm,parameters,stat);
        stat=header+comm+parameters+stat;//"play,ok,"+x+y+ficha;

        for(int i=0; i<jugadores.size(); i++)
        {
            connect_and_send(jugadores[i],stat);
        }
        turn=(++turn)%MAX_PLAYER;
    }
    else
    {
        header = make_header_response(comm,"","err");
        stat = header+comm+stat;
        connect_and_send(port_client,stat);
    }



}
int main(int argc, char *argv[])
{
    srand(time(0));

    int number_player=0;
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */
    int p;
    printf("puerto:\n");
    scanf("%d",&p);
    echoServPort = p;//atoi(argv[1]);  /* First arg:  local port */
    struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */
    pthread_t threadID;              /* Thread ID from pthread_create() */
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
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

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

    string stat="";
    int turn =0;
    for (;;) /* Run forever */
    {
        string command="";
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




        //tabla[clntSock]="";
        //jugadores.push_back(clntSock);
        int recvMsgSize=1;                    /* Size of received message */


        recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0);
        if ((recvMsgSize) <= 0)
        {
            printf("error handletcpclient_recv\n");
            return -2;
        }
        datos_protocol info;
        string port_client;
        string id;
        processing_format_protocol(port_client,id,info,echoBuffer);

       vector<string> datos_p = split(info.parameters,',');

        //string port_client=(datos_p[0]);
        string header;//=to_string( info.command.size() );
        if(info.command=="login")
        {
            int status =exist_user(port_client);
            stat=login(port_client,status);//intento registrar al usuario
            header = make_header_response(info.command,"",stat);
            stat=header+info.command+stat;
            connect_and_send(port_client,stat);

        }
        else if(info.command=="init")//port,nombre,tamaño,ficha,id
        {
            int status =exist_user(port_client);
            string nombre= datos_p[0];
            string tam_tabla=datos_p[1];
            stat = init_game(port_client,nombre,tam_tabla,status);

            header=make_header_response(info.command,"",stat);

            stat=header+info.command+stat;
            connect_and_send(port_client,stat);
        }
        else if(info.command=="join")//nombre id
        {
            int status =exist_user(port_client);
            string nombre = datos_p[0];
            string id=datos_p[1];
            stat = join(port_client,nombre,status);

            header = make_header_response(info.command,tam_tbl,stat);
            stat=header+info.command+tam_tbl+stat;

            connect_and_send(port_client,stat);

            if(jugadores.size()==MAX_PLAYER)
            {
                for(int i=0; i<jugadores.size(); i++)
                {
                    string comm = "start";
                    stat="ok";
                    // header = to_string(comm.size())+","+to_string(stat.size())+","+to_string(tam_tbl.size());

                    header=make_header_response(comm,tam_tbl,stat);
                    stat=header+comm+tam_tbl+stat;
                    connect_and_send(jugadores[i],stat);
                }
            }

        }
        else if(info.command=="play")//port,x,y,ficha,id
        {
            cout<<"tam users "<<users.size()<<" turno "<<turn<<endl;
            int status=exist_user(port_client);

            string x=datos_p[0];
            string y=datos_p[1];
            string ficha=datos_p[2];
            string id=datos_p[3];
            play(port_client,info.command,x,y,ficha,turn,status);
        }
        if(info.command=="finish")
        {
            //stat="finish,ok,"+users[datos_p[0]];
            string ganador=users[port_client];
            string header=make_header_response("finish",ganador,"ok");
            string stat=header+"finish"+ganador+"ok";
            for(int i=0; i<jugadores.size(); i++)
            {
                int rpt=connect_and_send(jugadores[i],stat);
            }
            users.clear();
            jugadores.clear();
            turn =0;
        }
        cout<<echoBuffer<<endl;

        close(clntSock);


        printf("with thread %ld\n", (long int) threadID);
    }
    /* NOT REACHED */
}



