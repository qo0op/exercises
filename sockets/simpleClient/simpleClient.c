#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8888
#define BUFF_SIZE 1024
#define IP_ADDR "127.0.0.1"

int main(int argc, char *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Socket creation error\n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, IP_ADDR, &serv_addr.sin_addr) <= 0)
	{
		printf("Invalid or not supported address\n");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Connection failed\n");
		return -1;
	}

	/* write, send difference */
	send(sock, hello, strlen(hello), 0);
	printf("\"%s\" sent to server\n", hello);
	valread = read(sock, buffer, BUFF_SIZE);
	printf("\"%s\" read from server\n", buffer);

	return 0;
}
