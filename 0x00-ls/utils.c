#include "headerls.h"

/**
  * count_characters - count the numbers of characters there is in a pointer
  * @directory_to_show_ls: pointer with the name of the directory
  * Return: the length of the name
  */
int count_characters(char *directory_to_show_ls)
{
	int index = 0;

	for (index = 0; directory_to_show_ls[index] != '\0'; index++)
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
  * Return: 1 if the tag exist otherwise 0
  */
int (*check_options_ok(int argc, char **argv))()
{
	int index = 0;
	tag_option choose[] = {
		{"", ls_basic},
		{"l", ls_options},
		{NULL, NULL},
	};

	if (argc > 1)
	{
		if (argv[1][0] == '-' && count_characters(argv[1]) != 1)
		{
			if (!(argv[1][1] == '-' && count_characters(argv[1]) == 2))
			{
				for (index = 1; choose[index].option != NULL; index++)
					if (argv[1][1] == choose[index].option[0])
						return (choose[index].function);
				return (choose[index].function);
			}
		}
	}
	return (choose[0].function);
}

/**
  * get_d_f_name - concatenate 2 strings
  * @argc: has the length of the arguments
  * @argv: has the arguments
  * @func: function pointer with the right function to use
  * Return: ponter with the two string concatenate
  */
char *get_d_f_name(int (*func)(struct dirent *, char *), int argc, char **argv)
{
	char *directory_to_show_ls = NULL;
	char *home = ".";

	if (func == ls_basic)
	{
		if (argc == 1)
			directory_to_show_ls = home;
		else
		{
			if ((count_characters(argv[1]) == 2) &&
				(argv[1][0] == '-') && (argv[1][1] == '-'))
				directory_to_show_ls = home;
			else
				directory_to_show_ls = argv[1];
		}
	}
	else
	{
		if (argc == 2)
			directory_to_show_ls = home;
		else
			directory_to_show_ls = argv[2];
	}

	return (directory_to_show_ls);
}
