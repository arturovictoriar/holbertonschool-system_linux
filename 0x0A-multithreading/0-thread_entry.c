#include "multithreading.h"

/**
* thread_entry -  entry point to a new thread
* @arg: address of a string that must be printed
* Return: Nothing
*/
void *thread_entry(void *arg)
{
	setbuf(stdout, NULL);
	printf("%s\n", (char *) arg);
	pthread_exit(NULL);
}
