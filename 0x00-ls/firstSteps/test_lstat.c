#include "headerls.h"

/**
  * extra_info_ls - get the state of a file or directory
  * @file_directory_to_show_state: has the file or directory name
  * @buffer: structure with the info state
  * Return: a structure with the state of a file o directory
  */
int extra_info_ls(char *file_directory_to_show_state, struct stat *buffer)
{
	int status = 0;

	if (file_directory_to_show_state == NULL)
	{
		printf("Choose a file or directory to get the state\n");
		return (1);
	}

	status = lstat(file_directory_to_show_state, buffer);
	if (status == -1)
		perror("Error");

	return (errno);
}
