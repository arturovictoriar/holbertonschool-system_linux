#include "syscalls.h"

/**
* main - use ptrace for getting the syscall name and return value
* @ac: number of arguments
* @av: list of arguments
* Return: 0 on success
*/
int main(int ac, char **av)
{
	pid_t child = 0;
	int status = 0, flag = -1;
	struct user_regs_struct regs;
	char *name = NULL;

	if (ac < 2)
	{
		printf("./strace_2 command [args...]\n");
		return (0);
	}
	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, child, NULL, NULL);
		raise(SIGSTOP);
		execve(av[1], &(av[1]), NULL);
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
				printf("%s = 0x%lx\n", name, (unsigned long)regs.rax);
			else if (WSTOPSIG(status) == SIGTRAP && (flag == -1 || flag == 0))
				name = (char *) syscalls_64_g[(unsigned long) regs.orig_rax].name;
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			flag = (flag == 0) ? 1 : 0;
		}
		printf("%s = ?\n", name);
	}
	return (0);
}
