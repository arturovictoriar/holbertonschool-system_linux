#include "headerls.h"

/**
 * _strcmp - compare 2 string.
 * @s1: is a pointer type char
 * @s2: is a pointer type char
 * Return: 0 on success otherwise other value.
 */
int _strcmp(char *s1, char *s2)
{
	int result = -1, i = 0;

	for (i = 0; s1 && s2 && s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] == s2[i])
			result = (s1[i] - '0') - (s2[i] - '0');
		else
		{
			result = (s1[i] - '0') - (s2[i] - '0');
			break;
		}
	}

	if (!(s1[i] == '\0' && s2[i] == '\0'))
		result = -1;

	return (result);
}

/**
 * get_options - get the index of the correct function
 * @argv: has the arguments
 * @option_tag_ls: options tags of ls
 * @i_argv: iterative index of argv
 * Return: if a tag does not exist return -1 otherwise a positive number
 */
int get_options(char **argv, int i_argv, char **option_tag_ls)
{
	int exist_flag = 0, i_one_argv, index = 0, func = 0;
	tag_option choose[] = {
		{"", ls_basic},
		{"1", ls_1_flg},
		{NULL, NULL},
	};

	for (i_one_argv = 1; argv[i_argv][i_one_argv] != '\0'; i_one_argv++)
	{
		exist_flag = 0;
		for (index = 1; choose[index].option != NULL; index++)
		{
			if (argv[i_argv][i_one_argv] == choose[index].option[0])
			{
				exist_flag = 1;
				func = 1;
				break;
			}
		}
		if (!exist_flag)
		{
			if (argv[i_argv][1] != '-')
				*option_tag_ls = &(argv[i_argv][i_one_argv]);
			else
				*option_tag_ls = argv[i_argv];
			return (-1);
		}
	}
	return (func);
}
