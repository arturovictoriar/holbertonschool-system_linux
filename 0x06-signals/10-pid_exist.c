#include <sys/types.h>
#include <signal.h>

/**
* pid_exist - check if a pid exist
* @pid: process id
* Return: 1 on succes, 0 otherwise
*/
int pid_exist(pid_t pid)
{
	return ((kill(pid, 0) == 0) ? 1 : 0);
}
