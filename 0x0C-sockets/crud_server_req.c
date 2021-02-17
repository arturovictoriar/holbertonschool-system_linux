#include "crud.h"

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
 * client_req - handle the client request
 * @socket_server: file descriptor of the server
 * Return: nothing
 */
void client_req(int socket_server)
{
	int socket_client = 0, client_size = 0, req_size = 0;
	struct sockaddr_in addr_client;
	char req[BUFFER_SIZE] = {0};
	http_msg_t req_data;
	todo_db_t *db;

	db = create_todo_db();
	if (!db)
		err_socket("Create todo db failed");
	while (1)
	{
		/*Waiting a client connection*/
		memset(&req_data, '\0', sizeof(http_msg_t));
		memset(req, '\0', BUFFER_SIZE);
		client_size = sizeof(addr_client);
		socket_client = accept(socket_server, (struct sockaddr *) &addr_client, (
					(socklen_t *) &client_size));
		if (socket_client == -1)
			err_socket("accept failed");
		/*Get the client request*/
		req[0] = '\0';
		req_size = recv(socket_client, req, BUFFER_SIZE - 1, 0);
		if (req_size == -1)
		{
			err_socket("recieve failed");
		}
		else if (req_size > 0)
		{
			req[req_size] = '\0';
			/*Parse the client request and response according to the request*/
			req_data = parse_req(req);
			req_data.client = inet_ntoa(addr_client.sin_addr);
			req_data.todo_db = db;
			client_res(socket_client, &req_data);
		}
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

	setbuf(stdout, NULL);
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
