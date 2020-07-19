#include "headerls.h"

/**
  * create_error_denied - create a custom error message permision denied
  * @d_ls: pointer with the name of the directory
  * @h_permi: all no open directory permission denied
  * Return: 0 on sucess
  */
int create_error_denied(char *d_ls, char **h_permi)
{
	char cannot_open_directory_message[] = "hls: cannot open directory ";
	char permission_denied[] = ": Permission denied";
	char *error_ls_message = NULL, *t_mes = NULL, *add_p_denied = NULL;

	error_ls_message = cannot_open_directory_message;
	t_mes = concat_two_strings(d_ls, error_ls_message);
	add_p_denied = concat_two_strings(permission_denied, t_mes);
	ls_1_flag_m_generetor(add_p_denied, h_permi);
	free_memory_messages(t_mes);
	free_memory_messages(add_p_denied);
	return (0);
}

/**
  * create_file_list - create list of files
  * @d_ls: pointer with the name of the directory
  * @i_f: get the file that no was open because are file
  * @f: function pointer with the right function to use
  * Return: 0 on sucess
  */
int create_file_list(char *d_ls, char **i_f,
	int (*f)(struct dirent *, char *, char **, char **))
{
	if (f == ls_basic)
		ls_message_generator(d_ls, i_f);
	else if (f == ls_1_flg)
		ls_1_flag_m_generetor(d_ls, i_f);
	else if (f == ls_a_flg || f == ls_A_flg)
		ls_message_generator(d_ls, i_f);
	else if (f == ls_l_flg)
		ls_1_flag_m_generetor(d_ls, i_f);
	return (0);
}

/**
  * e_alert - create a custom error message with perror
  * @d_ls: pointer with the name of the directory
  * @i_f: get the file that no was open because are file
  * @f: function pointer with the right function to use
  * @h_permi: all no open directory permission denied
  * Return: erron value or 1 if malloc fails
  */
int e_alert(char *d_ls, char **i_f, char **h_permi,
	int (*f)(struct dirent *, char *, char **, char **))
{
	char cannot_access_message[] = "hls: cannot access ";
	char dir_no_exis[] = ": No such file or directory", *ugo_permision = NULL;
	struct stat buffer = {0};
	int exist_file = 0;

	exist_file = extra_info_ls(d_ls, &buffer);
	if (!exist_file)
	{
		ugo_permision = get_ugo_permisions(&buffer);
		if (ugo_permision[0] != '-' && ugo_permision[1] == '-')
		{
			create_error_denied(d_ls, h_permi);
			free_memory_messages(ugo_permision);
			return (2);
		}
		else if (ugo_permision[0] == '-')
		{
			create_file_list(d_ls, i_f, f);
			free_memory_messages(ugo_permision);
			return (0);
		}
	}
	fprintf(stderr, "%s%s%s\n", cannot_access_message, d_ls,
		dir_no_exis);
	return (2);
}

/**
  * error_malloc - create a custom error message with perror when malloc fails
  * Return: exit status errno
  */
void error_malloc(void)
{
	fprintf(stderr, "Malloc error");
	exit(1);
}

/**
  * error_option - create a custom error message with perror
  * @option_tag_ls: pointer with the name of the directory
  * Return: erron value or 1 if malloc fails
  */
int error_option(char *option_tag_ls)
{
	char unrecognized_message[] = "hls: unrecognized option";
	char invalid_message[] = "hls: invalid option --";
	char help_message[] = "Try 'hls --help' for more information.";

	if (option_tag_ls && option_tag_ls[1] == '-')
	{
		if (option_tag_ls)
			fprintf(stderr, "%s '%s'\n%s\n",
				unrecognized_message, option_tag_ls, help_message);
	}
	else
	{
		if (option_tag_ls)
			fprintf(stderr, "%s '%c'\n%s\n",
				invalid_message, option_tag_ls[0], help_message);
	}

	return (2);
}
