#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

void panic(const char *msg)
{
    fprintf(stderr, "ERROR: %s", msg);
    exit(-1);
}

int main(int argc, char const *argv[])
{
    int fd_sock, port_number, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFER_SIZE];
    if (argc < 3)
        panic("Usage: client <hostname> <port>");

    port_number = atoi(argv[2]);
    fd_sock = socket(AF_INET, SOCK_STREAM, 0); // Se obtiene un descriptor de un socket TPC
    if (fd_sock < 0)
        panic("Could not open socket");

    server = gethostbyname(argv[1]);
    if (server == NULL)
        panic("Could not get host");

    // Configura serv_addr
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(
        (char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(port_number);

    // Se establece una conexión con el servidor
    int connect_result = connect(fd_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (connect_result < 0)
        panic("Could not connect");

    printf("Enter your name:\n>> ");

    memset(buffer, 0, BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE - 1, stdin);
    n = write(fd_sock, buffer, strlen(buffer));
    if (n < 0)
        panic("Could not write to socket");

    memset(buffer, 0, BUFFER_SIZE);
    n = read(fd_sock, buffer, BUFFER_SIZE - 1);
    if (n < 0)
        panic("Could not read from socket");
    printf("Message recieved: %s\n", buffer);

    return 0;
}
