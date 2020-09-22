#include "signals.h"


/**
* current_handler_signal - check the current handler
* Return: NULL or the pointer the current handler
*/
void (*current_handler_signal(void))(int)
{
	void (*handler)(int);

	handler = signal(SIGINT, NULL);
	signal(SIGINT, handler);
	return (handler);
}
