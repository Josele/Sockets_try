CC=gcc
CFLAGS=-g -Wall -O -I. 
LDFLAGS=
LDLIBS=
all :  Server Cliente

Server :  LibSock/Socket_Servidor.o LibSock/Socket.o LibSock/fsm.o Server.o

Cliente : LibSock/Socket_Cliente.o LibSock/Socket.o Cliente.o 


clean:
	$(RM) *.o *~ m Server Cliente LibSock/*.o LibSock/*.~

