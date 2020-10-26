#include "signals.h"

/**
* current_handler_sigaction - get a handler
* for the signal SIGINT with sigaction
* Return: pointer to handler on succes, otherwise NULL
*/
void (*current_handler_sigaction(void))(int)
{
	struct sigaction old_action;

	if (sigaction(SIGINT, NULL, &old_action) == -1)
		return (NULL);

	return (old_action.sa_handler);
}
