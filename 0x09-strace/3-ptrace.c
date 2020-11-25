#include "syscalls.h"


/**
 * print_parameters - print the parametres of a given syscall
 * @regs: struct with the register syscall
 * Return: nothing
 */
void print_parameters(struct user_regs_struct regs)
{
	unsigned long para[6] = {0};
	size_t nb_params, i = 0;

	para[0] = (unsigned long) regs.rdi;
	para[1] = (unsigned long) regs.rsi;
	para[2] = (unsigned long) regs.rdx;
	para[3] = (unsigned long) regs.r10;
	para[4] = (unsigned long) regs.r8;
	para[5] = (unsigned long) regs.r9;

	nb_params = syscalls_64_g[(unsigned long)regs.orig_rax].nb_params;

	while (i < nb_params)
	{
		if (i > 0)
			printf(", ");
		if (syscalls_64_g[(unsigned long) regs.orig_rax].params[i] == VARARGS)
			printf("...");
		else if (syscalls_64_g[(unsigned long) regs.orig_rax].params[i] != VOID)
			printf("%#lx", para[i]);
		i++;
	}
}


/**
 * main - use ptrace for getting the syscall name and return value
 * @ac: number of arguments
 * @av: list of arguments
 * @en: list of environ variables
 * Return: 0 on success, 1 otherwise
 */
int main(int ac, char **av, char **en)
{
	pid_t child = 0;
	int status = 0, flag = 0;
	struct user_regs_struct regs;

	if (ac < 2)
	{
		printf("./strace_3 command [args...]\n");
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
			if (flag)
				(printf(") = %#lx\n", (unsigned long) regs.rax), flag = 0);
			if (WSTOPSIG(status) == SIGTRAP && (long) regs.rax == -38)
				(printf("%s(",
					(char *) syscalls_64_g[(unsigned long)regs.orig_rax].name),
				 print_parameters(regs), flag = 1);
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		}
		printf(") = ?\n");
	}
	return (0);
}
