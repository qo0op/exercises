#include <stdio.h>
#include <string.h> // strlen
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <unistd.h> // write

int main(int argc, char *argv[])
{
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;
	char client_message[2000];

	/* Create socekt */
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		puts("Couldn't create socket");
	}
	puts("Socket created");

	/* Define socaddr_in structure */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	/* Bind the socket */
	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Error: Socket bind");
		return 1;
	}
	puts("Socket binding successful");

	/* Listen on socket for incomming traffc */
	listen(socket_desc, 3);

	/* Wait for incomming connections*/
	puts("Waiting for connections ...");
	c = sizeof(struct sockaddr_in);

	/* Accept incomming client connections */
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
	if(client_sock < 0)
	{
		perror("Accept failed");
		return 1;
	}
	puts("Connection accepted");

	/* Wait for client's message */
	while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
	{
		/* Echo => send the message back to client */
		write(client_sock, client_message, strlen(client_message));
		puts("Message echoed");
	}

	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		puts("Receive failed");
	}

	return 0;
}