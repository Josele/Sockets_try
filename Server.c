#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "Socket_Servidor.h"
#include "Socket.h"
#include "fsm.h"
#define MAXDATASIZE 100
#define PORT 45000
static char buf[MAXDATASIZE];  
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
{
 if(-1==Lee_Socket(Des_Clit,buf,1)){
printf("error de lectura\n");
return 0;}
return 1;
}
static int sckt_instruc (fsm_t* this)
{
 if(-1==Lee_Socket(Des_Clit,buf,(int)buf[0])){
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
send(Des_Clit,"OK",2,0);
}
static void  execute (fsm_t* this)
{
printf ("Soy servidor, He recibido : %s\n", buf);
	//ejecutamos y respondemos con el OK o error
send(Des_Clit,"OK",2,0);


}
static void finish (fsm_t* this)
{


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
}
