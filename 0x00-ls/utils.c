#include "headerls.h"

/**
  * count_characters - count the numbers of characters there is in a pointer
  * @directory_to_show_ls: pointer with the name of the directory
  * Return: the length of the name
  */
int count_characters(char *directory_to_show_ls)
{
	int index = 0;

	for (index = 0; directory_to_show_ls &&
		directory_to_show_ls[index] != '\0'; index++)
		continue;
	return (index);
}

/**
  * concat_two_strings - concatenate 2 strings
  * @str1: pointer with a string
  * @str2: pointer with a string
  * Return: ponter with the two string concatenate
  */
char *concat_two_strings(char *str1, char *str2)
{
	char *full_str = NULL;
	int str1_length = 0;
	int str2_length = 0;
	int index = 0;

	str1_length = count_characters(str1);
	str2_length = count_characters(str2);

	full_str = malloc((sizeof(char) * (str1_length + str2_length)) + 1);

	if (!full_str)
		return (NULL);

	for (index = 0; index <= (str2_length + str1_length); index++)
	{
		if (index < str2_length)
		{
			full_str[index] = str2[index];
		}
		else
			full_str[index] = str1[index - str2_length];
		if (index == (str2_length + str1_length))
			full_str[index] = '\0';
	}

	return (full_str);
}

/**
  * check_options_ok - check if the tag option exist
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * @option_tag_ls: options tags of ls
  * Return: 1 if the tag exist otherwise 0
  */
int (*check_options_ok(int argc, char **argv, char **option_tag_ls))()
{
	int i_argv = 0, flag_opt = 0, func = 0;
	tag_option choose[] = {
		{"", ls_basic},
		{"1", ls_1_flg},
		{"a", ls_a_flg},
		{NULL, NULL},
	};

	if (argc > 1)
	{
		if (argc == 2 && argv[1][0] == '-' &&
			count_characters(argv[1]) == 2 && argv[1][1] == '-')
			return (choose[0].function);
		for (i_argv = 1; i_argv < argc; i_argv++)
		{
			if (argv[i_argv][0] == '-' && count_characters(argv[i_argv]) != 1)
			{
				if (argv[i_argv][1] == '-' &&
					count_characters(argv[i_argv]) == 2)
				{
					if (!flag_opt)
						return (choose[0].function);
					break;
				}
				else
					func = get_options(argv, i_argv, option_tag_ls, choose);
				if (!flag_opt)
					flag_opt = 1;
				if (func == -1)
					return (NULL);
			}
		}
		if (flag_opt)
			return (choose[func].function);
	}
	return (choose[0].function);
}

/**
  * g_name - concatenate 2 strings
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * @f: function pointer with the right function to use
  * @index: position in argc of the directory to read
  * Return: ponter with the two string concatenate
  */
char *g_name(int f, int argc, char **argv, int index)
{
	char *directory_to_show_ls = NULL;

	if (f)
		directory_to_show_ls = get_proper_basic_dir(argc, argv, index);
	else
		directory_to_show_ls = get_proper_option_dir(argc, argv, index);

	return (directory_to_show_ls);
}

/**
  * choose_value_start - choose the rigth name of directory
  * @argc: has the length of the arguments
  * @f: function pointer with the right function to use
  * Return: the rigth name of directory
  */
int choose_value_start(int argc,
	int (*f)(struct dirent *, char *, char **, char **))
{
	int start_num = 0;

	if (f == ls_basic)
	{
		if (argc > 1)
			start_num = 1;
	}
	else
		start_num = 1;
	return (start_num);
}
