#include "syscalls.h"
#include <sys/ptrace.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <string.h>

/**
* wait_entry_quit_syscall - wait until ptrace say there is entry or quit sysc
* @child: pid child
* @status: status of ptrace in child process
* Return: 0 on succes, otherwise 1
*/
int wait_entry_quit_syscall(pid_t child, int status)
{
	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
			return (1);
	}
}

/**
* main - get the syscall number for a child process
* @ac: numbers of arguments
* @av: list of arguments
* @en: list of environ variables
* Return: 0 on sucess, 1 otherwise
*/
int main(int ac, char **av, char **en)
{
	pid_t child = 0;
	int status = 0;
	struct user_regs_struct regs;

	if (ac < 2)
	{
		printf("./strace_0 command [args...]\n");
		return (1);
	}
	fflush(stdout);
	child = fork();
	if (child == -1)
	{
		printf("Fork failed\n");
		return (1);
	}
	else if (child == 0)
	{
		ptrace(PTRACE_TRACEME, child, NULL, NULL);
		raise(SIGSTOP);
		execve(av[1], &(av[1]), en);
	}
	else
	{
		waitpid(child, &status, 0);
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
		while (1)
		{
			if (wait_entry_quit_syscall(child, status))
				break;
			memset(&regs, 0, sizeof(regs));
			ptrace(PTRACE_GETREGS, child, 0, &regs);
			printf("%ld\n", (long)regs.orig_rax);
			if (wait_entry_quit_syscall(child, status))
				break;
		}
	}
	fflush(stdout);
	return (0);
}
