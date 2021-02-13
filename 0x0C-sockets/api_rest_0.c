#include "api.h"

/**
 * parse_req - parse the request
 * @req: request
 * Return: status code to res client
 */
int parse_req(char *req)
{
	char *method = NULL, *path = NULL, *version = NULL, DELIM[] = " \xD\xA";

	/*split the start-line*/
	method = strtok(req, DELIM);
	path = strtok(NULL, DELIM);
	version = strtok(NULL, DELIM);
	printf("Method: %s\nPath: %s\nVersion: %s\n", method, path, version);

	return (200);
}

/**
 * client_res - handle the client response
 * @socket_client: client file descritor
 * @status: status response
 * Return: nothing
 */
void client_res(int socket_client, int status)
{
	int res_size = 0;
	char res[BUFFER_SIZE] = {0};

	switch (status)
	{
		case 200:
			sprintf(res, "HTTP/1.1 200 OK%s%s", CRLF, CRLF);
			break;
	}
	/*Send a response to the client*/
	res_size = strlen(res);
	if (send(socket_client, res, res_size, 0) != res_size)
		err_socket("send res failed");
}
