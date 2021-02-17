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
