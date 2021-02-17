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
	int res_size = 0, status = 0;
	char res[BUFFER_SIZE] = {0};

	/*print_http_msg(req_data);*/
	/*Check if the current request is a valid request*/
	status = check_req(req_data);
	create_res(status, req_data, res);
	/*Send a response to the client*/
	res_size = strlen(res);
	if (send(socket_client, res, res_size, 0) != res_size)
		err_socket("send res failed");
}
