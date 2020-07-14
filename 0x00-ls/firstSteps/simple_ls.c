
#include "headerls.h"

/**
  * ls_basic - list the directory o file given in argv without options
  * @read: has the length of the arguments
  * Return: nothing
  */
void ls_basic(struct dirent *read)
{
	printf("%s\n", read->d_name);
}

/**
  * ls_options - list the directory o file given in argv with options
  * @read: string with the name of the file listed
  * @directory_to_show_ls: string with the name of the directory list
  * Return: nothing
  */
void ls_options(struct dirent *read, char *directory_to_show_ls)
{
	struct stat buffer = {0};
	char *file_or_directory = NULL;
	char *d_name_d = NULL;
	long size_f_or_d = 0;
	char *ugo_permision = NULL;
	char *time = NULL;

	d_name_d = add_bar_diagonal_end(read->d_name);
	file_or_directory = concat_two_strings(d_name_d, directory_to_show_ls);
	free_memory_messages(d_name_d);
	extra_info_ls(file_or_directory, &buffer);
	ugo_permision = get_ugo_permisions(&buffer);
	time = get_time_file_directory(&buffer);
	size_f_or_d = get_size_file_directory(&buffer);
	printf("%s %ld %s %s\n", ugo_permision, size_f_or_d, time, read->d_name);
	free_memory_messages(ugo_permision);
	free_memory_messages(file_or_directory);
}

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
			{
				ls_basic(read);
			}
			else if (argc == 3)
			{
				ls_options(read, argv[1]);
			}
		}
		closedir(dir);
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
