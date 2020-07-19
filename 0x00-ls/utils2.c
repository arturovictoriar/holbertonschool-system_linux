#include "headerls.h"

/**
  * print_all_output - print the ls content in stdout
  * @ls_complete_message: pointer with the complete list file and dir
  * @is_file: pointer with the file could no open because are file
  * @h_permi: all file no have permission
  * @option_tag_ls: all option selected
  * @error_flag1: file or directory no found error
  * Return: errno or 2
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
	if (error_flag)
		return (error_flag);
	return (errno);
}
