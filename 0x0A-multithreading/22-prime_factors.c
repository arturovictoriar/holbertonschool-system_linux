#include "multithreading.h"

/**
 * create_task - create task structure
 * @entry: is a pointer to the entry function of the task
 * @param: is the parameter that will later be passed to the entry function
 * Return: a pointer to the created task structure
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *new_task = NULL;

	new_task = calloc(1, sizeof(task_t));
	if (!new_task)
		return (NULL);

	new_task->entry = entry;
	new_task->param = param;
	new_task->status = PENDING;
	new_task->result = NULL;
	/*	new_task->lock = PTHREAD_MUTEX_INITIALIZER;*/

	return (new_task);
}

/**
 * destroy_task - destroy task structure
 * @task:  pointer to the task to destroy
 * Return: Nothing
 */
void destroy_task(task_t *task)
{
	if (task->result)
	{
		list_destroy((list_t *) task->result, free);
		free((list_t *) task->result);
	}
	free(task);
}

/**
 * exec_tasks - run through the list of tasks and execute them
 * @tasks: pointer to the list of tasks to be executed
 * Return: return NULL as its return value will not be retrieved
 */
void *exec_tasks(list_t const *tasks)
{
	node_t *node = NULL;
	task_t *task = NULL;
	int i = 0;

	node = tasks->head;
	while (node)
	{
		task = (task_t *) node->content;
		if (task->status == PENDING)
		{
			task->status = STARTED;
			tprintf("[%02d] Started\n", i);
			task->result = (void *)
				(((list_t *(*) (char const *)) task->entry)((char const *) task->param));
			tprintf("[%02d] Success\n", i);
			if (task->result == NULL)
				task->status = FAILURE;
			else
				task->status = SUCCESS;
		}
		node = node->next;
		i++;
	}

	return (NULL);
}
