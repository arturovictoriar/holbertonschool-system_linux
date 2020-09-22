#include "signals.h"

/**
* main - print the str name of a signal
* @argc: number of arguments
* @argv: arguments
* Return: 0 on success, 1 otherwise
*/
int main(int argc, char **argv)
{
	char *name_exe = argv[0], *num_sig = argv[1];

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", name_exe);
		return (EXIT_FAILURE);
	}
	printf("%s: %s\n", num_sig, strsignal(atoi(num_sig)));

	return (0);
}
