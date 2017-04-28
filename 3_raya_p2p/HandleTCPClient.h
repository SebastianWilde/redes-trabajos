#include"game.h"


#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include<ctype.h>
#include <regex>
#include<bits/stdc++.h>
using namespace std;

const int RCVBUFSIZE =40;   /* Size of receive buffer */
const int HEADERSIZE=12;//tamaño del header para envios
const int HEADER_RESPONSE_SIZE=9; //tamaño del header para respuestas

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}




void removeCharsFromString( string &str, char* charsToRemove ) {
    for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
        str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}
int str_to_int(string s)
{

    string str = s;
    istringstream buffer(str);
    int value;
    buffer >> value;
    return value;
}
bool verify_format_coord(string input)
{
    string raw_pattern=R"([0-9]+,[0-9]+)";
    regex integer(raw_pattern);

    return regex_match(input,integer);
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

struct datos_protocol {

    string command;
    string parameters;
    datos_protocol(string c,string dat)
    {
        command=c;
        parameters=dat;

    }
    datos_protocol() {}
};

void processing_format_protocol(string&port_client,string &_id,datos_protocol & info, char * echoBuffer) {

    printf("\nline a procesar %s\n",echoBuffer);

    string port;
    string command;
    string parameters;
    string id;

    string dat = string(echoBuffer);
    string header_raw= dat.substr(0,HEADERSIZE);
    dat = dat.substr(HEADERSIZE,dat.size()-HEADERSIZE);//saco al header

    cout<<"header raw "<<header_raw<<" dat client "<<dat<<endl;
    vector<string>   header;// = split(header_raw,',');
    header.push_back(header_raw.substr(0,3));
    header.push_back(header_raw.substr(3,3));
    header.push_back(header_raw.substr(6,3));
    header.push_back(header_raw.substr(9,3));





    int ini=0;
    int sig=str_to_int(header[0]);
    port = dat.substr(ini,sig);
    ini+=sig;
    sig=str_to_int(header[1]);

    command = dat.substr(ini,sig);

    ini+=sig;
    sig=str_to_int(header[2]);

    parameters= dat.substr(ini,sig);

    ini+=sig;
    sig=str_to_int(header[3]);

    id= dat.substr(ini,sig);

    cout<<"puerto "<<port <<" command "<<command<<" parameters "<<parameters<<" id "<<id<<endl;
    datos_protocol information(command,parameters);//creo struct
    info=information;
    port_client =port;
    _id=id;
}
string make_header_send(string port, string command,string parameters, string id)
{
    string header;
    string port_len= to_string(port.size());
    string command_len=to_string(command.size());
    string parameters_len = to_string(parameters.size());
    string id_len=to_string(id.size());

    header+=string(3-port_len.size(),'0').append(port_len);
    header+=string(3-command_len.size(),'0').append(command_len);
    header+=string(3-parameters_len.size(),'0').append(parameters_len);
    header+=string(3-id_len.size(),'0').append(id_len);

    return header;
}
string make_header_response(string  command,string parameters, string status)
{

    string header;

    string command_len=to_string(command.size());
    string parameters_len = to_string(parameters.size());
    string status_len=to_string(status.size());

    header+=string(3-command_len.size(),'0').append(command_len);
    header+=string(3-parameters_len.size(),'0').append(parameters_len);
    header+=string(3-status_len.size(),'0').append(status_len);

    return header;

}
void processing_format_protocol_server(string& status,datos_protocol & info,char * echoBuffer) {

    printf("\nline a procesar %s\n",echoBuffer);

    string command;
    string parameters;

    string dat = string(echoBuffer);
    string header_raw= dat.substr(0,HEADER_RESPONSE_SIZE);
    dat = dat.substr(HEADER_RESPONSE_SIZE,dat.size()-HEADER_RESPONSE_SIZE);//saco al header
    cout<<"header raw "<<header_raw<<" datos "<<dat<<endl;
    vector<string>   header;// = split(header_raw,',');

    header.push_back(header_raw.substr(0,3));
    header.push_back(header_raw.substr(3,3));
    header.push_back(header_raw.substr(6,3));



    int ini=0;
    int sig=str_to_int(header[0]);

    command = dat.substr(ini,sig);

    ini+=sig;
    sig=str_to_int(header[1]);

    parameters= dat.substr(ini,sig);

    ini+=sig;
    sig=str_to_int(header[2]);


    status = dat.substr(ini,sig);



    cout<<"datos desde el servidor: \n";
    cout<<"command "<<command<<" parameters "<<parameters<<" status "<<status<<endl;
    datos_protocol information(command,parameters);//creo struct
    info=information;
    status=status;
}

//envio msj
int HandleTCPClient_send(int clntSocket,char echoBuffer[RCVBUFSIZE])
{
    // char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int len_send=0;
    printf("enviare servidor: ");



    printf("Sending:<%s>\n",echoBuffer);
    /* Echo message back to client */
    if((len_send=send(clntSocket, echoBuffer, RCVBUFSIZE, MSG_NOSIGNAL)!=RCVBUFSIZE))
    {
        printf("no se pudo mandar :(\n");
        return -2;
    }


    printf("fin envio \n");

    return -1;

}


void close_client(int clntSocket)
{
    close(clntSocket);
}


int connect_and_send(string p,string parameters)
{
    cout<<"conectando a "<<p<<endl;
    char echoBuffer[RCVBUFSIZE];
    struct sockaddr_in stSockAddr;
    int SocketFD = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP

    if (-1 == SocketFD)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(str_to_int(p) );
    cout<<"puerto a conectar "<<p<<endl;
    int Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);

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
        return -1;
    }

    strcpy(echoBuffer, parameters.c_str());

    HandleTCPClient_send(SocketFD,echoBuffer);

    close(SocketFD);
    cout<<"conexion con "<<SocketFD<<" cerrada "<<endl;
    return 0;
}
