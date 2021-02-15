#include "api.h"

/**
 * parse_req - parse the request
 * @req: request
 * Return: status code to res client
 */
int parse_req(char *req)
{
	char *path = NULL, DELIM[] = " \xD\xA", *data = NULL, *c_path = NULL;
	char *query = NULL, *save_query = NULL, *key = NULL, *value = NULL;

	/*split the start-line*/
	strtok(req, DELIM);
	c_path = strtok(NULL, DELIM);
	path = strtok(c_path, "?");
	printf("Path: %s\n", path);
	/*Split the query*/
	query = strtok(NULL, "?");
	save_query = query;
	data = strtok_r(query, "&", &save_query);
	while (data)
	{
		/*Split the key and value*/
		key = strtok(data, "=");
		value = strtok(NULL, "=");
		printf("Query: \"%s\" -> \"%s\"\n", key, value);
		data = strtok_r(NULL, "&", &save_query);
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
