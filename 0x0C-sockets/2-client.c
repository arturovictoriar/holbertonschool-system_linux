#include "sockets.h"

/**
 * err_socket - pritn the error message when socket app fails
 * @msg: message to print
 * Return: nothing
 */
void err_socket(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on
 * port 12345 (Any address).
 * @ac: number of arguments
 * @av: list of arguments
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int  socket_client = 0, server_size = 0, port = 0;
	struct sockaddr_in addr_server;
	char *host = NULL, msg[128] = {0};

	if (ac != 3)
	{
		sprintf(msg, "Usage: %s <host> <port>", av[0]);
		err_socket(msg);
	}

	host = av[1];
	port = atoi(av[2]);

	/*Create the file descriptor for a socket server*/
	socket_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_client == -1)
		err_socket("socket failed");
	/*Connet the socket with the server*/
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(port);
	addr_server.sin_addr.s_addr = strcmp("localhost", host) ? inet_addr(host) :
		inet_addr("127.0.0.1");

	server_size = sizeof(addr_server);
	if (connect(socket_client, (struct sockaddr *) &addr_server, server_size) ==
			-1)
		err_socket("connection failed");
	/*Print when the socket stablish connection with the server*/
	printf("Connected to %s:%d\n", host, port);
	close(socket_client);
	return (0);
}
