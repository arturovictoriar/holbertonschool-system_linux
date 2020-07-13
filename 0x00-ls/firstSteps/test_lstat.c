#include "headerls.h"

/**
  * extra_info_ls - get the state of a file or directory
  * @directory_to_show_ls: has the file or directory name
  * Return: a structure with the state of a file o directory
  */
void extra_info_ls(char *directory_to_show_ls)
{
	struct stat buffer;
	int status = 0;

	if (directory_to_show_ls == NULL)
	{
		printf("Choose a file or directory to get the state\n");
		return;
	}

	status = lstat(directory_to_show_ls, &buffer);
	if (status == -1)
	{
		perror("Error");
		return;
	}
}
