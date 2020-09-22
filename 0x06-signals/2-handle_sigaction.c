#include "signals.h"


/**
* int_signal - print gotcha when a sigint signal execute
* @signal_i: current signal
* Return: nothing
*/
void int_signal(int signal_i)
{
	printf("Gotcha! [%d]\n", signal_i);
}

/**
* handle_sigaction - set a handler for the signal SIGINT with sigaction
* Return: 0 on succes, otherwise -1
*/
int handle_sigaction(void)
{
	struct sigaction new_action;

	new_action.sa_handler = int_signal;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	return (sigaction(SIGINT, &new_action, NULL));
}
