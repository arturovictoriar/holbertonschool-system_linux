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
