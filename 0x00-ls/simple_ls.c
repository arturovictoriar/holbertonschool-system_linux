
#include "headerls.h"

/**
  * ls_basic - list the directory o file given in argv without options in a lin
  * @read: has the length of the arguments
  * @directory_to_show_ls: string with the name of the directory list
  * @ls_c_mes: ls complete message
  * @option_tag_ls: all option selected
  * Return: 0 on sucess
  */
int ls_basic(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_mes, char **option_tag_ls)
{
	(void) directory_to_show_ls;
	(void) option_tag_ls;

	if (read->d_name[0] != '.')
		return (ls_message_generator(read->d_name, ls_c_mes));
	return (0);
}

/**
  * ls_1_flg - list the directory o file given in argv without options in lines
  * @read: has the length of the arguments
  * @directory_to_show_ls: string with the name of the directory list
  * @ls_c_mes: ls complete message
  * @option_tag_ls: all option selected
  * Return: 0 on sucess
  */
int ls_1_flg(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_mes, char **option_tag_ls)
{
	(void) directory_to_show_ls;
	(void) option_tag_ls;

	if (read->d_name[0] != '.')
		return (ls_1_flag_m_generetor(read->d_name, ls_c_mes));
	return (0);
}

/**
  * ls_options - list the directory o file given in argv with options
  * @read: string with the name of the file listed
  * @directory_to_show_ls: string with the name of the directory list
  * @ls_c_me: ls complete message
  * @option_tag_ls: all option selected
  * Return: nothing
  */
int ls_options(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_me, char **option_tag_ls)
{
	struct stat buffer = {0};
	char *file_or_directory = NULL, *d_name_d = NULL, *ugo_permision = NULL;
	char *time = NULL, *user_id = NULL, *group_id = NULL;
	long size_f_or_d = 0;
	(void) ls_c_me;
	(void) option_tag_ls;

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
  * ls_metho - list the directory o file given in argv
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * @option_tag_ls: all option selected
  * @f: function pointer with the right function to use
  * Return: 0 to indicate a good working of the program otherwise errno value
  */
int ls_metho(int argc, char **argv, char **option_tag_ls,
	int (*f)(struct dirent *, char *, char **, char **))
{
	DIR *dir = NULL;
	struct dirent *read = NULL;
	char *directory_to_show_ls = NULL, *ls_complete_message = NULL;
	char *temp_message = NULL, *is_file = NULL, *h_permi = NULL;
	int f_s_c = 1, index = 0, start_num = 0;
	(void) option_tag_ls;

	if (f != ls_basic)
		f_s_c = 0;
	start_num = choose_value_start(argc, f);

	for (index = 0; index < argc - start_num; index++)
	{
		temp_message = NULL;
		directory_to_show_ls = g_name(f_s_c, argc, argv, index + start_num);
		if (!directory_to_show_ls)
			continue;
		dir = opendir(directory_to_show_ls);
		if (dir)
		{
			mul_name(argc, start_num, index, argv, &ls_complete_message, f_s_c);
			while ((read = readdir(dir)) != NULL)
			{
				f(read, directory_to_show_ls, &temp_message, option_tag_ls);
			}
			if (temp_message)
			{
				add_list_f_d(temp_message, &ls_complete_message);
				free_memory_messages(temp_message);
			}
			closedir(dir);
		}
		else
			e_alert(directory_to_show_ls, &is_file, f, &h_permi);
	}
	if (ls_complete_message || is_file || h_permi)
		print_list_ls(&ls_complete_message, &is_file, &h_permi);
	if (*option_tag_ls)
		free_memory_messages(*option_tag_ls);
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
	char *option_tag_ls = NULL;
	int end_status = 0;
	int (*function)(struct dirent *, char *, char **, char **) = NULL;

	/* Check if exist the tag name*/
	function = check_options_ok(argc, argv, &option_tag_ls);
	if (function)
	{
		/* Call ls funciontion*/
		end_status = ls_metho(argc, argv, &option_tag_ls, function);
		if (!end_status)
			return (end_status);
	}
	else
		end_status = error_option(option_tag_ls);

	if (end_status == 20)
		return (0);
	if (end_status > 2)
		end_status = 2;
	return (end_status);
}
