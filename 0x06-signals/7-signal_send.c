#include "signals.h"

/**
* main - send a sigint signal to a process
* @argc: number of arguments
* @argv: arguments
* Return: 0 on success, 1 otherwise
*/
int main(int argc, char **argv)
{
	char *name_exe = argv[0], *_pid = argv[1];

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", name_exe);
		return (EXIT_FAILURE);
	}

	if (kill(atoi(_pid), SIGINT))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
