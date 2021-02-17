#include "crud.h"

/**
 * post_method - create a todo if the request is right
 * @req_data: http message
 * Return: the status of the response
 */
int post_method(http_msg_t *req_data)
{
	char *content_len = NULL, *title = NULL, *description = NULL;
	todo_t *new_todo = NULL;

	(void) content_len;
	/*Look for Content-Lenght in headers*/
	parse_content_length(&content_len, req_data);
	if (!content_len)
		return (LENGTH_REQUIRED);

	/*Look for title and decription in body*/
	parse_title_description(&title, &description, req_data);
	if (!title || !description)
		return (UNPRO_ENTITY);

	/*Save the new todo*/
	new_todo = save_new_todo(title, description, req_data);
	if (!new_todo)
		err_socket("Create todo failed");

	return (CREATED);
}

/**
 * post_res - create the post response
 * @status: response status
 * @req_data: http message
 * @res: response store
 * Return: 1 on status found, otherwise 0
 */
int post_res(int status, http_msg_t *req_data, char *res)
{
	int res_size = 0, cont_len = 0;

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
		default:
			return (0);
	}
	return (1);
}
