#include "headerls.h"

/**
  * print_all_output - print the ls content in stdout
  * @ls_complete_message: pointer with the complete list file and dir
  * @is_file: pointer with the file could no open because are file
  * @h_permi: all file no have permission
  * @option_tag_ls: all option selected
  * @error_flag1: file or directory no found error
  * Return: 0 on success otherwise 2
  */
int print_all_output(char **is_file, char **h_permi,
	char **ls_complete_message, char **option_tag_ls, int error_flag1)
{
	int error_flag = 0;

	if (*h_permi || error_flag1)
		error_flag = 2;
	if (*ls_complete_message || *is_file || *h_permi)
		print_list_ls(ls_complete_message, is_file, h_permi);
	if (*option_tag_ls)
		free_memory_messages(*option_tag_ls);
	return (error_flag);
}

/**
 * _strcmp_real - compare 2 string.
 * @s1: is a pointer type char
 * @s2: is a pointer type char
 * Return: 0 on success otherwise other value.
 */
int _strcmp_real(char *s2, char *s1)
{
	int result = 0, i = 0;

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] == s2[i])
			result = (s1[i] - '0') - (s2[i] - '0');
		else
		{
			result = (s2[i] - '0') - (s1[i] - '0');
			break;
		}
	}
	return (result);
}

/**
  * order_argv - order alphabeticly the argv
  * @argv: has the arguments
  * Return: 0 to indicate a good working of the program
  */
int order_argv(char **argv)
{
	int cur_index = 0, nex_index = 0;
	char *tmp = NULL;

	for (cur_index = 1; argv[cur_index]; cur_index++)
	{
		for (nex_index = 1; argv[nex_index]; nex_index++)
		{
			if (_strcmp_real(argv[cur_index], argv[nex_index]) < 0)
			{
				tmp = argv[cur_index];
				argv[cur_index] = argv[nex_index];
				argv[nex_index] = tmp;
			}
		}
	}
	return (0);
}
