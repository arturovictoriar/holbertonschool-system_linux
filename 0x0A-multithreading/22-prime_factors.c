#include "multithreading.h"

/**
* create_task - create task structure
* @entry: is a pointer to the entry function of the task
* @param: is the parameter that will later be passed to the entry function
* Return: a pointer to the created task structure
*/
task_t *create_task(task_entry_t entry, void *param)
{
	(void) entry;
	(void) param;

	return (NULL);
}

/**
* destroy_task - destroy task structure
* @task:  pointer to the task to destroy
* Return: Nothing
*/
void destroy_task(task_t *task)
{
	(void) task;
}

/**
* exec_tasks - run through the list of tasks and execute them
* @tasks: pointer to the list of tasks to be executed
* Return: return NULL as its return value will not be retrieved
*/
void *exec_tasks(list_t const *tasks)
{
	(void) tasks;

	return (NULL);
}
