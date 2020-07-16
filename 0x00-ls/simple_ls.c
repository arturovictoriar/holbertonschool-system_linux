
#include "headerls.h"

/**
  * ls_basic - list the directory o file given in argv without options
  * @read: has the length of the arguments
  * @directory_to_show_ls: string with the name of the directory list
  * Return: nothing
  */
int ls_basic(struct dirent *read, char *directory_to_show_ls)
{
	(void) directory_to_show_ls;

	printf("%s\n", read->d_name);
	return (errno);
}

/**
  * ls_options - list the directory o file given in argv with options
  * @read: string with the name of the file listed
  * @directory_to_show_ls: string with the name of the directory list
  * Return: nothing
  */
int ls_options(struct dirent *read, char *directory_to_show_ls)
{
	struct stat buffer = {0};
	char *file_or_directory = NULL, *d_name_d = NULL, *ugo_permision = NULL;
	char *time = NULL, *user_id = NULL, *group_id = NULL;
	long size_f_or_d = 0;

	d_name_d = add_bar_diagonal_end(read->d_name);
	if (!d_name_d)
		error_malloc();

	file_or_directory = concat_two_strings(d_name_d, directory_to_show_ls);
	if (!file_or_directory)
		error_malloc();

	free_memory_messages(d_name_d);
	if (extra_info_ls(file_or_directory, &buffer))
		return (errno);

	ugo_permision = get_ugo_permisions(&buffer);
	if (!ugo_permision)
		error_malloc();

	time = get_time_file_directory(&buffer);
	if (!time)
		error_malloc();

	size_f_or_d = get_size_file_directory(&buffer);
	user_id = get_user_id_file_directory(&buffer);
	group_id = get_group_id_file_directory(&buffer);
	printf("%s %s %s %ld %s %s\n",
		ugo_permision, user_id, group_id, size_f_or_d, time, read->d_name);
	free_memory_messages(time);
	free_memory_messages(ugo_permision);
	free_memory_messages(file_or_directory);
	return (errno);
}

/**
  * ls_method - list the directory o file given in argv
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * @function: function pointer with the right function to use
  * Return: 0 to indicate a good working of the program otherwise errno value
  */
int ls_method(int argc, char **argv, int (*function)(struct dirent *, char *))
{
	DIR *dir = NULL;
	struct dirent *read = NULL;
	char *directory_to_show_ls = NULL;

	directory_to_show_ls = get_d_f_name(function, argc, argv);
	if (!directory_to_show_ls)
		return (2);

	dir = opendir(directory_to_show_ls);
	if (dir)
	{
		while ((read = readdir(dir)) != NULL)
		{
			function(read, directory_to_show_ls);
		}
		if (errno)
			return (errno);
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
	char *option_tag_ls = NULL;
	char home = '.';
	int end_status = 0;
	int (*function)(struct dirent *, char *) = NULL;

	function = check_options_ok(argc, argv);
	if (function)
	{
		/* Call ls funciontion*/
		end_status = ls_method(argc, argv, function);
		if (!end_status)
			return (end_status);
		/* If ls function fails, show a message error and set return value*/
		if (argc == 1)
			directory_to_show_ls = &home;
		else if (argc == 2)
			directory_to_show_ls = argv[1];
		else if (argc == 3)
			directory_to_show_ls = argv[2];
		else
			directory_to_show_ls = &home;

		end_status = error_alert(directory_to_show_ls);
	}
	else
	{
		option_tag_ls = argv[1];
		end_status = error_option(option_tag_ls);
	}

	return (end_status);
}
