#include "headerls.h"

/**
  * ls_message_generator - create the complete ls message
  * @d_f_name: pointer with the name of the directory or file
  * @ls_complet_message: pointer where the message will be store
  * Return: char pointer with the complete name
  */
int ls_message_generator(char *d_f_name, char **ls_complet_message)
{
	int num_mesa = 0;
	int num_name = 0;
	int complete_number = 0;
	int write_ok = 0;
	char *new_message = NULL;

	if (*ls_complet_message)
		num_mesa = count_characters(*ls_complet_message);
	num_name = count_characters(d_f_name);

	if (ls_complet_message)
		complete_number = (num_name + 2 + num_mesa + 1);
	else
		complete_number = num_name + 1;

	new_message = malloc(sizeof(char) * complete_number);
	if (!new_message)
		error_malloc();

	if (*ls_complet_message)
		write_ok = sprintf(new_message, "%s  %s", *ls_complet_message, d_f_name);
	else
		write_ok = sprintf(new_message, "%s", d_f_name);

	if (write_ok < 0)
		return (2);

	if (ls_complet_message)
		free_memory_messages(*ls_complet_message);

	*ls_complet_message = new_message;
	return (0);
}

/**
  * add_name_dir - add the directory name
  * @d_f_name: pointer with the name of the directory or file
  * @ls_complet_message: pointer where the message will be store
  * Return: char pointer with the complete name
  */
int add_name_dir(char *d_f_name, char **ls_complet_message)
{
	int num_mesa = 0;
	int num_name = 0;
	int complete_number = 0;
	int write_ok = 0;
	char *new_message = NULL;

	if (*ls_complet_message)
		num_mesa = count_characters(*ls_complet_message);
	num_name = count_characters(d_f_name);

	if (ls_complet_message)
		complete_number = (num_name + 3 + num_mesa + 1);
	else
		complete_number = num_name + 2;

	new_message = malloc(sizeof(char) * complete_number);
	if (!new_message)
		error_malloc();

	if (*ls_complet_message)
		write_ok = sprintf(new_message, "%s\n\n%s:", *ls_complet_message, d_f_name);
	else
		write_ok = sprintf(new_message, "%s:", d_f_name);

	if (write_ok < 0)
		return (2);

	if (ls_complet_message)
		free_memory_messages(*ls_complet_message);

	*ls_complet_message = new_message;
	return (0);
}

/**
  * add_list_f_d - add the list of file and directories
  * @d_f_name: pointer with the name of the directory or file
  * @ls_complet_message: pointer where the message will be store
  * Return: char pointer with the complete name
  */
int add_list_f_d(char *d_f_name, char **ls_complet_message)
{
	int num_mesa = 0;
	int num_name = 0;
	int complete_number = 0;
	int write_ok = 0;
	char *new_message = NULL;

	if (*ls_complet_message)
		num_mesa = count_characters(*ls_complet_message);
	num_name = count_characters(d_f_name);

	if (ls_complet_message)
		complete_number = (num_name + 1 + num_mesa + 1);
	else
		complete_number = num_name + 1;

	new_message = malloc(sizeof(char) * complete_number);
	if (!new_message)
		error_malloc();

	if (*ls_complet_message)
		write_ok = sprintf(new_message, "%s\n%s", *ls_complet_message, d_f_name);
	else
		write_ok = sprintf(new_message, "%s", d_f_name);

	if (write_ok < 0)
		return (2);

	if (ls_complet_message)
		free_memory_messages(*ls_complet_message);

	*ls_complet_message = new_message;
	return (0);
}

/**
  * mul_name - add the list of file and directories
  * @argc: pointer with the name of the directory or file
  * @s_num: start number in the argv
  * @i: index argv
  * @argv: arguments from enviorment
  * @ls_c: pointer where the message will be store
  * @f_s_c: ls basic 1 otherwise 0
  * Return: char pointer with the complete name
  */
int mul_name(int argc, int s_num, int i, char **argv, char **ls_c, int f_s_c)
{
	if (argc - s_num != 1)
	{
		{
			if (f_s_c)
				add_name_dir(argv[i + 1], ls_c);
			else
				add_name_dir(argv[i + 2], ls_c);
		}
	}
	return (0);
}

