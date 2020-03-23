WARNS=-Wextra -Wall -Wundef  -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code
CC=gcc
CFLAGS=$(WARNS)

all: client server

client: src/client.c 
	$(CC) -o build/client src/client.c

server: src/server.c
	$(CC) -o build/server src/server.c

.PHONY: clean
clean:
	@ -rm -f build/*