CC=gcc
CFLAGS=-g -Wall -O -I.
LDFLAGS=
LDLIBS=
all : Socket.o Socket_Servidor.o Socket_Cliente.o Server Cliente

Server : Server.o  Socket_Servidor.o Socket.o

Cliente : Cliente.c Socket_Cliente.o Socket.o

clean:
	$(RM) *.o *~ m Server Cliente

