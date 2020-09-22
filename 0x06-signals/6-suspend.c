#include "signals.h"

/**
* int_signal - print the sigint signal when execute
* @signal_i: signal number
* Return: nothing
*/
void int_signal(int signal_i)
{
	printf("Caught %d\n", signal_i);
}

/**
* main - wait until the signal sigint be executed
* Return: 0 on success
*/
int main(void)
{
	struct sigaction new_action;

	new_action.sa_handler = int_signal;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
