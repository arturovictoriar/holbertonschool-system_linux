#include "headerls.h"

/**
  * error_alert - create a custom error message with perror
  * @directory_to_show_ls: pointer with the name of the directory
  * Return: erron value or 1 if malloc fails
  */
int error_alert(char *directory_to_show_ls)
{
	char error_ls_message[] = "ls: cannot access ";
	char *error_message = NULL;

	error_message = concat_two_strings(directory_to_show_ls, error_ls_message);

	if (!error_message)
		return (1);

	perror(error_message);

	free_memory_messages(error_message);
	return (errno);
}
