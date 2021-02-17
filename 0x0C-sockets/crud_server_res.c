#include "crud.h"

/**
 * print_http_msg - show the request message parsed
 * @req_data: obj which store the request message
 * Return: nothing
 */
void print_http_msg(http_msg_t *req_data)
{
	printf("client = $%s$\n", req_data->client);
	printf("method = $%s$\n", req_data->method);
	printf("path = $%s$\n", req_data->path);
	printf("query = $%s$\n", req_data->query);
	printf("version = $%s$\n", req_data->version);
	printf("header = $%s$\n", req_data->headers);
	printf("body = $%s$\n", req_data->body);
	printf("status = $%d$\n", req_data->status);
}

/**
 * client_res - handle the client response
 * @socket_client: client file descritor
 * @req_data: request data parsed
 * Return: nothing
 */
void client_res(int socket_client, http_msg_t *req_data)
{
	int res_size = 0, cont_len = 0, status;
	char res[BUFFER_SIZE] = {0};

	/*print_http_msg(req_data);*/
	/*Check if the current request is a valid request*/
	status = check_req(req_data);
	switch (status)
	{
		case CREATED:
			printf("%s %s %s -> 201 Created\n",
					req_data->client, req_data->method, req_data->path);
			cont_len = sprintf(res, JSON_FORMAT, req_data->last_todo->id,
					req_data->last_todo->title, req_data->last_todo->description);
			res_size = sprintf(res, RES_201_FORMAT, cont_len, req_data->last_todo->id,
					req_data->last_todo->title, req_data->last_todo->description);
			res[res_size] = '\0';
			break;
		case NOT_FOUND:
			printf("%s %s %s -> 404 Not Found\n",
					req_data->client, req_data->method, req_data->path);
			sprintf(res, RES_404_FORMAT);
			break;
		case LENGTH_REQUIRED:
			printf("%s %s %s -> 411 Length Required\n",
					req_data->client, req_data->method, req_data->path);
			sprintf(res, RES_411_FORMAT);
			break;
		case UNPRO_ENTITY:
			printf("%s %s %s -> 422 Unprocessable Entity\n",
					req_data->client, req_data->method, req_data->path);
			sprintf(res, RES_422_FORMAT);
			break;
	}
	/*Send a response to the client*/
	res_size = strlen(res);
	if (send(socket_client, res, res_size, 0) != res_size)
		err_socket("send res failed");
}
