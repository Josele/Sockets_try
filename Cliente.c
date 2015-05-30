/*
* Javier Abellan, 20 Jun 2000
*
* Programa Cliente de un socket INET, como ejemplo de utilizacion
* de las funciones de sockets
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include "LibSock/Socket_Cliente.h"
#include "LibSock/Socket.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
int main (int argc, char *argv[])
{
	/*
	* Descriptor del socket y buffer para datos
	*/
	int Socket_Con_Servidor;
	char Cadena[100];
	char IP[]="192.168.1.38";
	char length[10];
	char valid[2];
	//strcpy (IP,"10.7.15.213");
	/*
	* Se abre la conexion con el servidor, pasando el nombre del ordenador
	* y el servicio solicitado.
	* "localhost" corresponde al nombre del mismo ordenador en el que
	* estamos corriendo. Esta dado de alta en /etc/hosts
	* "cpp_java" es un servicio dado de alta maen /etc/services
	*/
	Socket_Con_Servidor = Abre_Conexion_Inet (IP, 45000);
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		return (-1);
	}
	
	/*
	* Se prepara una cadena con 5 caracteres y se envia, 4 letras mas
	* el \0 que indica fin de cadena en C
	*/if(argc==1){
	length[0]=(char)12;
	memset(Cadena,'\0',100);
        strcpy (Cadena, "mi ejemplo f");
	}else
	{
	length[0]=(int)strlen(argv[1]);
	strcpy(Cadena,argv[1]);
	}
		
	Escribe_Socket (Socket_Con_Servidor, length, 1);
	
	/*
	* Se lee la informacion enviada por el servidor, que se supone es
	* una cadena de 6 caracteres.
	*/
		
	Lee_Socket (Socket_Con_Servidor, valid, 2);

	/*
	* Se escribe en pantalla la informacion recibida del servidor
	*/
	printf ("Soy cliente, He recibido : %s \n", valid);
	
	
	Escribe_Socket (Socket_Con_Servidor, Cadena,(int) length[0]);
	/*
	* Se cierra el socket con el servidor
	*/
	close (Socket_Con_Servidor);
return 0;
}
