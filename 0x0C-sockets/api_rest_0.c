#include "api.h"

#define BUFFER_SIZE 256
#define CRLF "\xD\xA"

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
* client_res - handle the client response
* @socket_client: client file descritor
* @req: request
* @res: response
* Return: nothing
*/
void client_res(int socket_client, char *req, char *res)
{
	int res_size = 0, i = 0;
	char *line1 = NULL, *tok = NULL;
	/*split the start-line*/
	line1 = strtok(req, "\n");
	if (line1 != NULL)
	{
		tok = strtok(line1, " ");
		i = 0;
		while (tok)
		{
			switch (i)
			{
				case 0:
					printf("Method: %s\n", tok);
					break;
				case 1:
					printf("Path: %s\n", tok);
					break;
				case 2:
					printf("Version: %s\n", tok);
					break;
			}
			tok = strtok(NULL, " ");
			i++;
		}
	}
	/*Send a good response to the client*/
	strcat(res, "HTTP/1.1 200 OK"), strcat(res, CRLF), strcat(res, CRLF);
	res_size = strlen(res);
	if (send(socket_client, res, res_size, 0) != res_size)
		err_socket("send res failed");
}

/**
 * client_req - handle the client request
 * @socket_server: file descriptor of the server
 * Return: nothing
 */
void client_req(int socket_server)
{
	int socket_client = 0, client_size = 0, req_size = 0;
	struct sockaddr_in addr_client;
	char req[BUFFER_SIZE] = {0}, res[BUFFER_SIZE] = {0};

	for (; ; memset(res, '\0', BUFFER_SIZE))
	{
		/*Waiting a client connection*/
		client_size = sizeof(addr_client);
		socket_client = accept(socket_server, (struct sockaddr *) &addr_client, (
					(socklen_t *) &client_size));
		if (socket_client == -1)
			err_socket("accept failed");
		/*Print the client connected and message recieved*/
		printf("Client connected: %s\n", inet_ntoa(addr_client.sin_addr));
		printf("Raw request: \"");
		for (; ; memset(req, '\0', BUFFER_SIZE))
		{
			req_size = recv(socket_client, req, BUFFER_SIZE - 1, 0);
			if (req_size == -1)
				err_socket("recieve failed");
			else if (req_size == 0)
				break;
			printf("%s", req);
			if (req[req_size - 2] == CRLF[0] && req[req_size - 1] == CRLF[1])
				break;
		}
		printf("\"\n");
		client_res(socket_client, req, res);
		close(socket_client);
	}
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
	addr_server.sin_family = AF_INET, addr_server.sin_port = htons(PORT);
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	server_size = sizeof(addr_server);
	if (bind(socket_server, (struct sockaddr *) &addr_server, server_size) == -1)
		err_socket("bind failed");
	/*Let the listening of the socket with 10 waiting clients*/
	if (listen(socket_server, NUM_CLNTS) == -1)
		err_socket("listen failed");
	printf("Server listening on port %d\n", PORT);
	client_req(socket_server);
	close(socket_server);
	return (0);
}
