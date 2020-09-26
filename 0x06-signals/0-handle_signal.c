#include "signals.h"

/**
* int_signal - print gotcha when a sigint execute
* @signal_i: current signal
* Return: nothing
*/
void int_signal(int signal_i)
{
	printf("Gotcha! [%d]\n", signal_i);
}


/**
* handle_signal - handle a sigint signal
* Return: 0 on success otherwise -1
*/
int handle_signal(void)
{
	if (signal(SIGINT, int_signal) == SIG_ERR)
		return (-1);
	return (0);
}
