#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BACKLOG_QUEUE_SIZE 5
#define BUFFER_SIZE 256

void panic(const char *msg)
{
    fprintf(stderr, "ERROR: %s", msg);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int fd_sock, fd_newsock; // Descriptores de archivo
    int port_number;         // Puerto en el que se aceptan conexiones
    int client_len;          // Tamaño de la dirección del cliente
    struct sockaddr_in serv_addr, cli_addr;
    int n; // Valor de retorno para read() y write()

    char buffer[BUFFER_SIZE]; // El servidor lee del socket y guarda en este buffer

    if (argc < 2)
        panic("No port provided");
    
    fd_sock = socket(AF_INET, SOCK_STREAM, 0); // Se obtiene un descriptor de un socket TCP
    if (fd_sock < 0)
        panic("Could not open socket");

    // Inicializa en 0s
    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    port_number = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;          // Ajusta el tipo de direcciones a Internet
    serv_addr.sin_port = htons(port_number); // Configura el puerto que se usa
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // Ajusta la IP a la de la máquina huesped

    int bind_result = bind(fd_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (bind_result < 0)
        panic("Binding failed");

    printf("Listening on port %d\n", port_number);

    // Esta operación NO DEBERIA fallar (?)
    listen(fd_sock, BACKLOG_QUEUE_SIZE);

    client_len = sizeof(cli_addr);

    // El proceso se bloquea hasta que algun cliente se conecta al servidor.
    // Se retorna un nuevo descriptor que debe ser utilizado para comunicarse durante esa conexión
    fd_newsock = accept(fd_sock, (struct sockaddr *)&cli_addr, &client_len);

    // Solo se alcanza esta sección si existe una conexión de algún cliente

    printf("Connection recieved...\n");
    // Inicializa en 0s
    memset(buffer, 0, BUFFER_SIZE);
    // El proceso se bloquea hasta que haya algo que leer (el cliente debe ejecutar `write`)
    n = read(fd_newsock, buffer, BUFFER_SIZE - 1);
    if (n < 0)
        panic("Could not read from socket");

    printf("Message recieved: %s\n", buffer);

    char result_msg[BUFFER_SIZE + 8];
    memset(result_msg, 0, BUFFER_SIZE + 8);
    strcpy(result_msg, "Hello, ");
    strcat(result_msg, buffer);

    n = write(fd_newsock, result_msg, BUFFER_SIZE + 8);
    if (n < 0)
        panic("Could not write to socket");

    return 0;
}