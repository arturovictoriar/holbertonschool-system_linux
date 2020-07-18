#include "headerls.h"

/**
  * error_alert - create a custom error message with perror
  * @directory_to_show_ls: pointer with the name of the directory
  * @is_file: get the file that no was open because are file
  * Return: erron value or 1 if malloc fails
  */
int error_alert(char *directory_to_show_ls, char **is_file)
{
	char cannot_access_message[] = "hls: cannot access ";
	char cannot_open_directory_message[] = "hls: cannot open directory ";
	char *error_ls_message = NULL;
	char *error_message = NULL;

	switch (errno)
	{
	case EACCES:
		error_ls_message = cannot_open_directory_message;
		break;
	case ENOENT:
		error_ls_message = cannot_access_message;
		break;
	case ENOTDIR:
		ls_message_generator(directory_to_show_ls, is_file);
		return (0);
	default:
		error_ls_message = cannot_open_directory_message;
		break;
	}
	error_message = concat_two_strings(directory_to_show_ls, error_ls_message);

	if (!error_message)
		error_malloc();

	perror(error_message);

	free_memory_messages(error_message);
	return (errno);
}

/**
  * error_malloc - create a custom error message with perror when malloc fails
  * Return: exit status errno
  */
void error_malloc(void)
{
	perror("Malloc error");
	exit(errno);
}

/**
  * error_option - create a custom error message with perror
  * @option_tag_ls: pointer with the name of the directory
  * Return: erron value or 1 if malloc fails
  */
int error_option(char *option_tag_ls)
{
	char unrecognized_message[] = "hls: unrecognized option";
	char invalid_message[] = "hls: invalid option --";
	char help_message[] = "Try 'hls --help' for more information.";

	if (option_tag_ls && option_tag_ls[1] == '-')
	{
		if (option_tag_ls)
			fprintf(stderr, "%s '%s'\n%s\n",
				unrecognized_message, option_tag_ls, help_message);
	}
	else
	{
		if (option_tag_ls)
			fprintf(stderr, "%s '%c'\n%s\n",
				invalid_message, option_tag_ls[0], help_message);
	}

	return (2);
}
