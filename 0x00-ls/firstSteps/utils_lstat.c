#include "headerls.h"

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
  * iniciatilize_string_permision - inicialize a string with '-' character
  * @file_directory_permisions: empty string
  * Return: a string initialized with '-' character
  */
char *iniciatilize_string_permision(char *file_directory_permisions)
{
	int index = 0;

	for (index = 0; index <= 10; index++)
	{
		if (index < 10)
			file_directory_permisions[index] = '-';
		else
			file_directory_permisions[index] = '\0';
	}
	return (file_directory_permisions);
}

/**
  * get_type_file_directory - get the type of the file stat
  * @buffer: structure with the info state
  * @file_dire_permisions: string representative of the permission
  * Return: string representative of the permission with thr type-file
  */
char *get_type_file_directory(struct stat *buffer, char *file_dire_permisions)
{
	switch (buffer->st_mode & S_IFMT)
	{
	case S_IFBLK:
		file_dire_permisions[0] = '-';
		break;
	case S_IFCHR:
		file_dire_permisions[0] = '-';
		break;
	case S_IFDIR:
		file_dire_permisions[0] = 'd';
		break;
	case S_IFIFO:
		file_dire_permisions[0] = '-';
		break;
	case S_IFLNK:
		file_dire_permisions[0] = '-';
		break;
	case S_IFREG:
		file_dire_permisions[0] = '-';
		break;
	case S_IFSOCK:
		file_dire_permisions[0] = '-';
		break;
	default:
		file_dire_permisions[0] = '-';
		break;
	}
	return (file_dire_permisions);
}

/**
  * get_rwx_permisions - get the read, write, execute permisions of a file
  * @buffer: structure with the info state
  * @file_directory_permisions: string representative of the permission
  * Return: string representative of the permission with the rwx permision
  */
char *get_rwx_permisions(struct stat *buffer, char *file_directory_permisions)
{
	if (buffer->st_mode & S_IRUSR)
		file_directory_permisions[1] = 'r';
	if (buffer->st_mode & S_IWUSR)
		file_directory_permisions[2] = 'w';
	if (buffer->st_mode & S_IXUSR)
		file_directory_permisions[3] = 'x';

	if (buffer->st_mode & S_IRGRP)
		file_directory_permisions[4] = 'r';
	if (buffer->st_mode & S_IWGRP)
		file_directory_permisions[5] = 'w';
	if (buffer->st_mode & S_IXGRP)
		file_directory_permisions[6] = 'x';

	if (buffer->st_mode & S_IROTH)
		file_directory_permisions[7] = 'r';
	if (buffer->st_mode & S_IWOTH)
		file_directory_permisions[8] = 'w';
	if (buffer->st_mode & S_IXOTH)
		file_directory_permisions[9] = 'x';

	return (file_directory_permisions);
}

/**
  * get_short_date - get short a full date
  * @full_date: string with a full date
  * Return: short date only with the month, day, hour and minutes
  */
char *get_short_date(char *full_date)
{
	char *short_date = NULL;
	int index = 0;

	short_date = malloc(sizeof(char) * 13);

	for (index = 0; index <= 12; index++)
	{
		if (index < 12)
			short_date[index] = full_date[index + 4];
		else
			short_date[index] = '\0';
	}

	return (short_date);
}
