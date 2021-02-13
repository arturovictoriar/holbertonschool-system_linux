#include "api.h"

/**
 * parse_req - parse the request
 * @req: request
 * Return: status code to res client
 */
int parse_req(char *req)
{
	int i = 0;
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
	char res[BUFFER_SIZE] = {0}, msg[512] = {0};

	switch (status)
	{
		case 200:
			strcpy(msg, "HTTP/1.1 200 OK");
			break;
	}
	/*Send a response to the client*/
	strcat(res, msg), strcat(res, CRLF), strcat(res, CRLF);
	res_size = strlen(res);
	if (send(socket_client, res, res_size, 0) != res_size)
		err_socket("send res failed");
}
