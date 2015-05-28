CC=gcc
CFLAGS=-g -Wall -O -I.
LDFLAGS=
LDLIBS=
all : Server 

Server : Server.o Socket_Servidor.o 

clean:
	$(RM) *.o *~ m Server

