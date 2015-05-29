/*
* Javier Abellan, 20 Jun 2000
*
* Programa Cliente de un socket INET, como ejemplo de utilizacion
* de las funciones de sockets
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include "Socket_Cliente.h"
#include "Socket.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
int main ()
{
	/*
	* Descriptor del socket y buffer para datos
	*/
	int Socket_Con_Servidor;
	char Cadena[100];
	char IP[]="10.7.15.171";
	strcpy (IP,"10.7.15.171");
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
	*/
	Cadena[0]=(char)8;
	
	
	Escribe_Socket (Socket_Con_Servidor, Cadena, 1);

	/*
	* Se lee la informacion enviada por el servidor, que se supone es
	* una cadena de 6 caracteres.
	*/
	Lee_Socket (Socket_Con_Servidor, Cadena, 2);

	/*
	* Se escribe en pantalla la informacion recibida del servidor
	*/
	printf ("Soy cliente, He recibido : %s\n", Cadena);
	strcpy (Cadena, "mi casa ");
	Escribe_Socket (Socket_Con_Servidor, Cadena, 1);
	/*
	* Se cierra el socket con el servidor
	*/
	close (Socket_Con_Servidor);
return 0;
}
