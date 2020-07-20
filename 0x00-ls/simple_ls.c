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
  * ls_l_flg - list the directory o file given in argv with options
  * @read: string with the name of the file listed
  * @directory_to_show_ls: string with the name of the directory list
  * @ls_c_me: ls complete message
  * @option_tag_ls: all option selected
  * Return: nothing
  */
int ls_l_flg(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_me, char **option_tag_ls)
{
	char *dir_all_opt = NULL;
	int ret_func = 0;
	(void) option_tag_ls;

	if (read->d_name[0] == '.')
		return (0);
	dir_all_opt = get_more_info_dir(read, directory_to_show_ls);
	ret_func = ls_1_flag_m_generetor(dir_all_opt, ls_c_me);
	free_memory_messages(dir_all_opt);
	return (ret_func);
}

/**
  * ls_metho - list the directory o file given in argv
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * @o_ls: all option selected
  * @f: function pointer with the right function to use
  * Return: 0 to indicate a good working of the program otherwise a number
  */
int ls_metho(int argc, char **argv, char **o_ls,
	int (*f)(struct dirent *, char *, char **, char **))
{
	DIR *dir = NULL;
	struct dirent *read = NULL;
	char *directory_to_show_ls = NULL, *ls_c_m = NULL;
	char *temp_message = NULL, *is_file = NULL, *h_permi = NULL;
	int f_s_c = 1, index = 0, start_num = 0, error_flag = 0, e_flag1 = 0;

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
			mul_name(argc, start_num, index, argv, &ls_c_m, f_s_c);
			while ((read = readdir(dir)) != NULL)
			{
				f(read, directory_to_show_ls, &temp_message, o_ls);
			}
			if (temp_message)
			{
				add_list_f_d(temp_message, &ls_c_m);
				free_memory_messages(temp_message);
			}
			closedir(dir);
		}
		else
			if (!e_flag1)
				e_flag1 = e_alert(directory_to_show_ls, &is_file, &h_permi, f);
			else
				e_alert(directory_to_show_ls, &is_file, &h_permi, f);
	}
	error_flag = print_all_output(&is_file, &h_permi, &ls_c_m, o_ls, e_flag1);
	return (error_flag);
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
		order_argv(argv);
		end_status = ls_metho(argc, argv, &option_tag_ls, function);
	}
	else
		end_status = error_option(option_tag_ls);

	return (end_status);
}
