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
  * add_bar_diagonal_end - concatenate a string with /
  * @str1: pointer with a string
  * Return: ponter with the two string concatenate
  */
char *add_bar_diagonal_end(char *str1)
{
	char *with_bar_diagonal = NULL;
	int str1_length = 0;
	int index = 0;

	str1_length = count_characters(str1);
	with_bar_diagonal = malloc((sizeof(char) * str1_length) + 2);
	if (!with_bar_diagonal)
		return (NULL);

	for (index = 0; index <= str1_length + 1; index++)
	{
		if (index == 0)
			with_bar_diagonal[index] = '/';
		else if (index <= str1_length)
			with_bar_diagonal[index] = str1[index - 1];
		else
			with_bar_diagonal[index] = '\0';
	}
	return (with_bar_diagonal);
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
