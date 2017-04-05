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
    string proc;
    char buffer[256];
    datosProtocol protocol;
    string name ;
    char ficha;
    proc = generarProtocolo(0 , name,ficha);
    strcpy(buffer, proc.c_str());
    procesarProtocolo(proc,protocol);
    cout<<"Este es el protocolo "<<proc<<endl;
    cout<<" este es una parte del protocolo "<<protocol.nombre;
    return 0;
  }