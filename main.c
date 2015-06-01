#include "Server.h"
#include <stdio.h>   
int main()
{int done2;
char* line;
fsm_t* serv_fsm = serv_init();
Des_Ser_init();
while(1){
 do{  
     done2=serv_state_trans (serv_fsm); 
    }while(!done2);  
        
                line =get_buff();
                printf ("Ejecutamos : %s\n", line);

}

return 0;
}