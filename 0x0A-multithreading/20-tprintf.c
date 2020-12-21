#include "multithreading.h"

static pthread_mutex_t lock_mutex;

void initialize_mutex(void) __attribute__((constructor));

void destroy_mutex(void) __attribute__((destructor));

/**
* initialize_mutex - initialize the mutex
* Return: Nothing
*/
void initialize_mutex(void)
{
	pthread_mutex_init(&lock_mutex, NULL);
}

/**
* destroy_mutex - destroy the mutex
* Return: Nothing
*/
void destroy_mutex(void)
{
	pthread_mutex_destroy(&lock_mutex);
}

/**
 * tprintf -  print out a given formatted string and the  calling thread ID
 * @format: is string format
 * Return: 0 on success
 */
int tprintf(char const *format, ...)
{
	va_list args;
	pthread_t self;

	pthread_mutex_lock(&lock_mutex);

	self = pthread_self();
	setbuf(stdout, NULL);
	va_start(args, format);
	printf("[%lu] ", self);
	vprintf(format, args);
	va_end(args);

	pthread_mutex_unlock(&lock_mutex);

	return (0);
}
