#include "headerls.h"

/**
  * get_size_file_directory - get the size of a file or directory
  * @buffer: structure with the info state
  * Return: size of a file o directory
  */
long get_size_file_directory(struct stat *buffer)
{
	return ((long) buffer->st_size);
}

/**
  * get_ugo_permisions - get the permision of a file or directory
  * @buffer: structure with the info state
  * Return: a string with the permisions of a file o directory
  */
char *get_ugo_permisions(struct stat *buffer)
{
	char *file_directory_permisions = NULL;

	file_directory_permisions = malloc(sizeof(char) * 11);
	if (!file_directory_permisions)
		return (NULL);

	iniciatilize_string_permision(file_directory_permisions);

	get_type_file_directory(buffer, file_directory_permisions);

	get_rwx_permisions(buffer, file_directory_permisions);

	return (file_directory_permisions);
}

/**
  * get_time_file_directory - get the time was created a file
  * @buffer: structure with the info state
  * Return: readable time string
  */
char *get_time_file_directory(struct stat *buffer)
{
	char *time = NULL;
	char *short_time = NULL;

	time = ctime(&(buffer->st_mtime));
	short_time = get_short_date(time);
	return (short_time);
}

/**
  * extra_info_ls - get the state of a file or directory
  * @file_directory_to_show_state: has the file or directory name
  * @buffer: structure with the info state
  * Return: a structure with the state of a file o directory
  */
int extra_info_ls(char *file_directory_to_show_state, struct stat *buffer)
{
	int status = 0;

	if (file_directory_to_show_state == NULL)
	{
		printf("Choose a file or directory to get the state\n");
		return (1);
	}

	status = lstat(file_directory_to_show_state, buffer);
	return (status);
}
