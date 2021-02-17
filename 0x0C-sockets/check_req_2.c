#include "crud.h"

/**
 * check_req - check if the given request is allowed
 * @req_data: http message parse
 * Return: the status of the request
 */
int check_req(http_msg_t *req_data)
{
	char *c_methods[] = {"POST", "GET", NULL}, *c_paths[] = {"/todos", NULL};
	char *method = NULL, *path = NULL;
	int m = 0, p = 0;

	/*Check out the methods available*/
	method = c_methods[m];
	while (method && req_data->method)
	{
		if (!strcmp(method, req_data->method))
			break;
		++m;
		method = c_methods[m];
	}
	/*Check out the paths available*/
	path = c_paths[p];
	while (path && req_data->path)
	{
		if (!strcmp(path, req_data->path))
			break;
		++p;
		path = c_paths[p];
	}
	/*If path and method exist in the server, call the according method*/
	if (method && path)
	{
		switch (m)
		{
			case POST:
				req_data->status = post_method(req_data);
				break;
			case GET:
				req_data->status = get_method(req_data);
				break;
		}
		return (req_data->status);
	}
	return (NOT_FOUND);
}

/**
 * create_res - create the response
 * @status: response status
 * @req_data: http message
 * @res: response store
 * Return: nothing
 */
void create_res(int status, http_msg_t *req_data, char *res)
{
	int method = 0;

	method = post_res(status, req_data, res);
	if (method)
		return;
	method = get_res(status, req_data, res);
	if (method)
		return;
}
