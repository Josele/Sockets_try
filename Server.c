#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>

#include "Socket_Servidor.h"
main()
{
int Des_Ser;
int Des_Clit;
Des_Ser=Abre_Socket_Inet ("192.168.1.41", 3550,2);
while(1){
Des_Clit=Acepta_Conexion_Cliente (Des_Ser);
send(Des_Clit,"Bienvenido a mi servidor.\n",22,0); 
      /* que enviará el mensaje de bienvenida al cliente */
close(Des_Clit); /* cierra fd2 */

}
}
