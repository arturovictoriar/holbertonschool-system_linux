#ifndef POOL_THREAD_H
#define POOL_THREAD_H

typedef void *(*task_entry_t)(void *);

/**
 * enum task_status_e - Task statuses
 *
 * @PENDING: Task is pending
 * @STARTED: Task has been started
 * @SUCCESS: Task has completed successfully
 * @FAILURE: Task has completed with issues
 */
typedef enum task_status_e
{
	PENDING = 0,
	STARTED,
	SUCCESS,
	FAILURE
} task_status_t;

/**
 * struct task_s - Executable task structure
 *
 * @entry:  Pointer to a function to serve as the task entry
 * @param:  Address to a custom content to be passed to the entry function
 * @status: Task status, default to PENDING
 * @result: Stores the return value of the entry function
 * @lock:   Task mutex
 */
typedef struct task_s
{
	task_entry_t    entry;
	void        *param;
	task_status_t   status;
	void        *result;
	pthread_mutex_t lock;
} task_t;

#endif
