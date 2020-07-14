#include "headerls.h"

/**
  * error_alert - create a custom error message with perror
  * @directory_to_show_ls: pointer with the name of the directory
  * Return: erron value or 1 if malloc fails
  */
int error_alert(char *directory_to_show_ls)
{
	char cannot_access_message[] = "ls: cannot access ";
	char cannot_open_directory_message[] = "ls: cannot open directory ";
	char *error_ls_message = NULL;
	char *error_message = NULL;

	switch (errno)
	{
	case EACCES:
		error_ls_message = cannot_open_directory_message;
		break;
	case ENOENT:
		error_ls_message = cannot_access_message;
		break;
	}
	error_message = concat_two_strings(directory_to_show_ls, error_ls_message);

	if (!error_message)
		error_malloc();

	perror(error_message);

	free_memory_messages(error_message);
	return (errno);
}

/**
  * error_malloc - create a custom error message with perror when malloc fails
  * Return: exit status errno
  */
void error_malloc(void)
{
	perror("Malloc error");
	exit(errno);
}
