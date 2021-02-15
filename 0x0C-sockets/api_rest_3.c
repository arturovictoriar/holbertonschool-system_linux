#include "api.h"

/**
 * parse_req - parse the request
 * @req: request
 * Return: status code to res client
 */
int parse_req(char *req)
{
	char *path = NULL, *value = NULL, *key = NULL;
	char *save_req = NULL, *body = NULL, *pair = NULL, *save_pair = NULL;
	char DELIM[] = "\xD\xA", BODY_SEPARATOR[] = "\xD\xA\xD\xA", *line1 = NULL;
	int i = 0;

	/*split the start-line*/
	save_req = req;
	line1 = strtok_r(req, DELIM, &save_req);
	/*Get the path*/
	strtok(line1, " ");
	path = strtok(NULL, " ");
	printf("Path: %s\n", path);
	/*Look for body data*/
	for (i = 0; save_req && save_req[i] != '\0'; i++)
	{
		if (save_req[i] == '\xD' && !strncmp(&save_req[i], BODY_SEPARATOR, 4))
			break;
	}
	if (!save_req || save_req[i] == '\0')
		return (400);
	req = &save_req[i];
	save_req = req;
	/*Get the body data*/
	body = strtok_r(req, DELIM, &save_req);
	while (body)
	{
		save_pair = body;
		pair = strtok_r(body, "&", &save_pair);
		/*Print the body data*/
		while (pair)
		{
			key = strtok(pair, "=");
			value = strtok(NULL, "=");
			printf("Body param: \"%s\" -> \"%s\"\n", key, value);
			pair = strtok_r(NULL, "&", &save_pair);
		}
		body = strtok_r(NULL, DELIM, &save_req);
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
