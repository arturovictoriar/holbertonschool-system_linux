#include "crud.h"

/**
 * delete_method - delete a given id if the request is right
 * @req_data: http message
 * Return: the status of the response
 */
int delete_method(http_msg_t *req_data)
{
	char *id = NULL;
	ssize_t n_id = 0;
	todo_t *todo = NULL, *pre_todo = NULL;

	parse_query_id(&id, req_data);
	if (id)
	{
		n_id = atoi(id);
		for (todo = req_data->todo_db->todos; todo; todo = todo->next)
		{
			if (todo->id == n_id)
				break;
			pre_todo = todo;
		}
		if (!todo)
			return (NOT_FOUND);
		if (!pre_todo && !todo->next)
			req_data->todo_db->todos = NULL, req_data->todo_db->last_id++;
		else if (!pre_todo && todo->next)
			req_data->todo_db->todos = todo->next;
		else if (pre_todo && !todo->next)
			pre_todo->next = NULL;
		else
			pre_todo->next = todo->next;
		free_todo(todo);
		return (NO_CONTENT);
	}
	return (NOT_FOUND);
}

/**
 * delete_res - create the delete response
 * @status: response status
 * @req_data: http message
 * @res: response store
 * Return: 1 on status found, otherwise 0
 */
int delete_res(int status, http_msg_t *req_data, char *res)
{
	int res_size = 0;

	switch (status)
	{
		case NO_CONTENT:
			printf("%s %s %s -> 204 No Content\n",
					req_data->client, req_data->method, req_data->path);
			res_size = sprintf(res, RES_204_FORMAT);
			res[res_size] = '\0';
			break;
		default:
			return (0);
	}
	return (1);
}
