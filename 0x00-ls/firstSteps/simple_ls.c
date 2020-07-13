
#include "headerls.h"

/**
  * ls_method - list the directory o file given in argv
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * Return: 0 to indicate a good working of the program otherwise errno value
  */
int ls_method(int argc, char **argv)
{
	DIR *dir = NULL;
	struct dirent *read = NULL;
	char *directory_to_show_ls = NULL;

	directory_to_show_ls = argv[1];
	dir = opendir(directory_to_show_ls);
	if (dir)
	{
		while ((read = readdir(dir)) != NULL)
		{
			if (argc == 2)
				printf("%s\n", read->d_name);
		}
		closedir(dir);
		return (0);
	}
	return (errno);
}

/**
  * main - list the files and folders of a directory
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * Return: 0 to indicate a good working of the program
  */
int main(int argc, char **argv)
{
	char *directory_to_show_ls = NULL;
	int end_status = 0;

	/*If no parameter pass to funciont, show a message and return fails value*/
	if (argc == 1)
	{
		printf("Choose a directory or a file\n");
		return (1);
	}
	/* Call ls funciontion*/
	end_status = ls_method(argc, argv);
	if (!end_status)
		return (end_status);
	/* If ls function fails, show a message error and set return value*/
	directory_to_show_ls = argv[1];
	end_status = error_alert(directory_to_show_ls);
	return (end_status);
}
