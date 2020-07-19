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
	int index = 0, count_ops = 0;

	for (index = 0; index < argc; index++)
		if (argv[index][0] == '-')
			count_ops++;

	if (f_s_c && argc - s_num - count_ops > 1)
		add_name_dir(argv[i + 1], ls_c);
	else if (!f_s_c && argc - s_num - count_ops >= 2)
		add_name_dir(argv[i + 1], ls_c);
	return (0);
}

/**
  * print_list_ls - print the ls content in stdout
  * @ls_complete_message: pointer with the complete list file and dir
  * @is_file: pointer with the file could no open because are file
  * @h_permi: all file no have permission
  * Return: 0 ok otherwise 1
  */
int print_list_ls(char **ls_complete_message, char **is_file, char **h_permi)
{
	if (*is_file)
	{
		printf("%s\n", *is_file);
		free_memory_messages(*is_file);
	}
	if (*ls_complete_message)
	{
		if (*is_file)
			printf("\n");
		printf("%s\n", *ls_complete_message);
		free_memory_messages(*ls_complete_message);
	}
	if (*h_permi)
	{
		fprintf(stderr, "%s\n", *h_permi);
		free_memory_messages(*h_permi);
	}
	return (0);
}
