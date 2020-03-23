IDIR=C:\tools\cygwin\usr\include
WARNS=-Wextra -Wall -Wundef  -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code
CC=gcc
CFLAGS=-I$(IDIR) $(WARNS)

all: client server

client: client.c 
	$(CC) -o client client.c

server: server.c
	$(CC) -o server server.c

.PHONY: clean
clean:
	-rm -f server.exe
	-rm -f client.exe