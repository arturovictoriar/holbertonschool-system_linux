#include "multithreading.h"

/**
* tprintf -  print out a given formatted string and the  calling thread ID
* @format: is string format
* Return: 0 on success
*/
int tprintf(char const *format, ...)
{
	va_list args;
	pthread_t self;

	self = pthread_self();
	setbuf(stdout, NULL);
	va_start(args, format);
	printf("[%lu] ", self);
	vprintf(format, args);
	va_end(args);

	return (0);
}
