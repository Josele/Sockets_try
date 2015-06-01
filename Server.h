#ifndef SERVER_H
#define SERVER_H
#include "LibSock/fsm.h"
void Des_Ser_init();
fsm_t* serv_init();
void serv_state_trans(fsm_t* serv_fsm);



#endif