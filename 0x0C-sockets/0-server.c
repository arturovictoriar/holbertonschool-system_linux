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
 * Return: 0 on success
 */
int main(void)
{
	int socket_server = 0, server_size = 0;
	struct sockaddr_in addr_server;

	/*Create the file descriptor for a socket server*/
	socket_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_server == -1)
		err_socket("socket failed");
	/*Bind the socket with a port and an address in ipv4*/
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(PORT);
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);

	server_size = sizeof(addr_server);
	if (bind(socket_server, (struct sockaddr *) &addr_server, server_size) == -1)
		err_socket("bind failed");
	/*Let the listening of the socket with 10 waiting clients*/
	if (listen(socket_server, NUM_CLNTS) == -1)
		err_socket("listen failed");
	/*Waiting a client connection*/
	printf("Socket server listen on port %d\n", PORT);
	while (1)
		;

	return (0);
}
