#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "LibSock/Socket_Servidor.h"
#include "LibSock/Socket.h"
#include "LibSock/fsm.h"
#define MAXDATASIZE 100
#define PORT 45000
static char buf[MAXDATASIZE];  
volatile int tam;
volatile static int Des_Ser;
volatile static int Des_Clit;
enum serv_state {
  SERV_APT,
  SERV_RECV,
  SERV_RECVINST,
  SERV_CLOSE,
};

static int conexion_start (fsm_t* this)
{
 if(-1==(Des_Clit=Acepta_Conexion_Cliente (Des_Ser)))
 return 0;

return 1;
}

static int sckt_weight (fsm_t* this)
{//int resultado=recvform(Des_Clit,buf,MAXDATASIZE,);
 if(-1==Lee_Socket(Des_Clit,buf,1)){
printf("error de lectura\n");
return 0;}
tam=(int)buf[0];
printf ("Soy servidor, He recibido : %d\n", tam);

return 1;
}
static int sckt_instruc (fsm_t* this)
{
 if(-1==Lee_Socket(Des_Clit,buf,tam)){
printf("error de lectura\n");

return 0;
}

return 1;
}


static int sckt_close (fsm_t* this)
{

close(Des_Clit); /* cierra fd2*/ 

return 1;
}

static void something (fsm_t* this)
{

}


static void  ack (fsm_t* this)
{
memset(buf,'\0',MAXDATASIZE);
strcpy (buf, "OK");
Escribe_Socket (Des_Clit, buf, 2);
memset(buf,'\0',MAXDATASIZE);
}
static void  execute (fsm_t* this)
{
printf ("Soy servidor, He recibido : %s\n", buf);

	//ejecutamos y respondemos con el OK o error
send(Des_Clit,"OK",2,0);


}
static void finish (fsm_t* this)
{
memset(buf,'\0',MAXDATASIZE);

// podemos añadir un flag con un flag con un break etc

}
// Explicit FSM description
static fsm_trans_t serv[] = {
  { SERV_APT, conexion_start, SERV_RECV,  something},
  { SERV_RECV,     sckt_weight, SERV_RECVINST,  ack },
  { SERV_RECVINST,  sckt_instruc, SERV_CLOSE,    execute   },
  { SERV_CLOSE,sckt_close, SERV_APT, finish },
  {-1, NULL, -1, NULL },
};

int main()
{


Des_Ser=Abre_Socket_Inet (PORT,1);
  
  fsm_t* serv_fsm = fsm_new (serv);
while(1){

 fsm_fire (serv_fsm); 
}

return 0;
}/*
*Lo más facil y elegante es añadir getter y setters. Lanzando la máquina de estado en el interp, el getter sería como un notify.
*Lo más rapido es rehacer el interp para que convivan con los sockets
*Otras opciones son hebras y punteros.
int socket_interp()
{


Des_Ser=Abre_Socket_Inet (PORT,1);
  
  fsm_t* serv_fsm = fsm_new (serv);
while(1){

 fsm_fire (serv_fsm); 
}

return 0;
}*/