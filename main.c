#include "Server.h"
#include <stdio.h>   
int main()
{

fsm_t* serv_fsm = serv_init();
Des_Ser_init();
while(1){

 serv_state_trans (serv_fsm); 
}

return 0;
}