#include "crud.h"

/**
* create_todo_db - create a list of todos
* Return: a pointer of the list of todo, NULL otherwise
*/
todo_db_t *create_todo_db(void)
{
	todo_db_t *new_db = NULL;

	new_db = malloc(sizeof(todo_db_t));
	if (!new_db)
		return (NULL);

	new_db->todos = NULL;
	new_db->last_id = 0;

	return (new_db);
}

/**
* create_todo - create a single todo
* Return: a pointer of a todo, NULL otherwise
*/
todo_t *create_todo(void)
{
	todo_t *new_todo = NULL;

	new_todo = malloc(sizeof(todo_t));
	if (!new_todo)
		return (NULL);

	new_todo->title = NULL;
	new_todo->description = NULL;
	new_todo->id = 0;
	new_todo->next = NULL;

	return (new_todo);
}

/**
* save_new_todo - save a new todo in db
* @title: todo title
* @description: todo description
* @req_data: http mesagge
* Return: a pointer with the new todo save in db, NULL otherwise
*/
todo_t *save_new_todo(char *title, char *description, http_msg_t *req_data)
{
	todo_t *new_todo = NULL, *node = NULL;

	new_todo = create_todo();
	if (!new_todo)
		return (NULL);

	new_todo->title = strdup(title);
	new_todo->description = strdup(description);

	if (!req_data->todo_db->todos)
	{
		req_data->todo_db->todos = new_todo;
		new_todo->id = req_data->todo_db->last_id;
	}
	else
	{
		node = req_data->todo_db->todos;
		while (node->next)
			node = node->next;
		node->next = new_todo;
		new_todo->id = req_data->todo_db->last_id + 1;
	}
	req_data->todo_db->last_id = new_todo->id;

	req_data->last_todo = new_todo;

	return (new_todo);
}

/**
* free_todo - free a todo
* @todo: todo to free
* Return: nothing
*/
void free_todo(todo_t *todo)
{
	if (todo)
	{
		if (todo->title)
			free(todo->title);
		if (todo->description)
			free(todo->description);
		free(todo);
	}
}
