#include "syscalls.h"

/**
* main - use ptrace for getting the syscall name
* @ac: number of arguments
* @av: list of arguments
* @en: list of environ variables
* Return: 0 on success, 1 otherwise
*/
int main(int ac, char **av, char **en)
{
	pid_t child = 0;
	int status = 0, flag = -1;
	struct user_regs_struct regs;
	unsigned long name = 0;

	if (ac < 2)
	{
		printf("./strace_0 command [args...]\n");
		return (1);
	}
	setbuf(stdout, NULL);
	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, child, NULL, NULL);
		raise(SIGSTOP);
		execve(av[1], &(av[1]), en);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (0);
		ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		while (wait(&status) && !WIFEXITED(status))
		{
			memset(&regs, 0, sizeof(regs));
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (WSTOPSIG(status) == SIGTRAP && flag == 1)
				printf("%lu\n", name);
			else if (WSTOPSIG(status) == SIGTRAP && (flag == -1 || flag == 0))
				name = (unsigned long) regs.orig_rax;
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			flag = (flag == 0) ? 1 : 0;
		}
		printf("%lu\n", name);
	}
	return (0);
}
