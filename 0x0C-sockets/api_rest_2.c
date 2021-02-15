#include "api.h"

/**
 * parse_req - parse the request
 * @req: request
 * Return: status code to res client
 */
int parse_req(char *req)
{
	char *header = NULL, *key_header = NULL, DELIM[] = "\xD\xA";
	char *save_header = NULL, *value_header = NULL;
	char *is_more_data = NULL, *colon = NULL, *value_header_plus = NULL;

	/*split the start-line*/
	save_header = req;
	strtok_r(req, DELIM, &save_header);
	header = strtok_r(NULL, DELIM, &save_header);
	while (header)
	{
		key_header = strtok(header, ":");
		value_header = strtok(NULL, ":");
		is_more_data = strtok(NULL, ":");
		value_header_plus = is_more_data ? is_more_data : "";
		colon = is_more_data ? ":" : "";
		printf("Header: \"%s\" -> \"%s%s%s\"\n", key_header, &value_header[1],
				colon, value_header_plus);
		header = strtok_r(NULL, DELIM, &save_header);
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
