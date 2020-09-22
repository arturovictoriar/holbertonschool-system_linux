#include "signals.h"

/**
* quit_signal - print the pid of the program who sent a quit signal
* @signum: signal number
* @info: struct with information of the signal
* @ptr: ucontext structure
* Return: nothing
*/
void quit_signal(int signum, siginfo_t *info, void *ptr)
{
	(void) signum;
	(void) ptr;

	printf("SIGQUIT sent by %d\n", (int) info->si_pid);
}

/**
* trace_signal_sender - get information of the signal sender
* Return: 0 on succes, 1 otherwise
*/
int trace_signal_sender(void)
{
	struct sigaction new_action;

	new_action.sa_sigaction = quit_signal;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = SA_SIGINFO;

	return (sigaction(SIGQUIT, &new_action, NULL));
}
