#include "crud.h"

/**
 * get_method - get all the todos if the request is right
 * @req_data: http message
 * Return: the status of the response
 */
int get_method(http_msg_t *req_data)
{
	char *id = NULL;
	ssize_t n_id = 0;
	todo_t *todo = NULL;

	parse_query_id(&id, req_data);
	if (id)
	{
		n_id = atoi(id);
		for (todo = req_data->todo_db->todos; todo; todo = todo->next)
		{
			if (todo->id == n_id)
				break;
		}
		if (!todo)
			return (NOT_FOUND);
		req_data->last_todo = todo;
	}
	else
	{
		req_data->last_todo = NULL;
	}
	return (OK);
}

/**
 * get_res - create the get response
 * @status: response status
 * @req_data: http message
 * @res: response store
 * Return: 1 on status found, otherwise 0
 */
int get_res(int status, http_msg_t *req_data, char *res)
{
	char json[BUFFER_SIZE / 2] = {0}, todo_dict[BUFFER_SIZE / 8] = {0};
	int res_size = 0, cont_len = 0;
	todo_t *todo = NULL;

	switch (status)
	{
		case OK:
			printf("%s %s %s -> 200 OK\n",
					req_data->client, req_data->method, req_data->path);
			if (req_data->last_todo)
			{
				todo = req_data->last_todo;
				cont_len = sprintf(todo_dict, JSON_FORMAT, todo->id, todo->title,
						todo->description);
				res_size = sprintf(res, RES_200_FORMAT, cont_len, todo_dict);
			}
			else
			{
				json[cont_len] = '[';
				for (todo = req_data->todo_db->todos; todo; todo = todo->next)
				{
					cont_len = sprintf(todo_dict, JSON_FORMAT, todo->id, todo->title,
							todo->description);
					if (todo->next)
						todo_dict[cont_len] = ',', ++cont_len;
					todo_dict[cont_len] = '\0';
					strcat(json, todo_dict);
				}
				cont_len = strlen(json);
				json[cont_len] = ']';
				++cont_len;
				json[cont_len] = '\0';
				res_size = sprintf(res, RES_200_FORMAT, cont_len, json);
			}
			res[res_size] = '\0';
			break;
		default:
			return (0);
	}
	return (1);
}
