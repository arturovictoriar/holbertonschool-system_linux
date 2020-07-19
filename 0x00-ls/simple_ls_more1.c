#include "headerls.h"

/**
  * ls_a_flg - list all directory including hidden files
  * @read: has the length of the arguments
  * @directory_to_show_ls: string with the name of the directory list
  * @ls_c_mes: ls complete message
  * @option_tag_ls: all option selected
  * Return: 0 on sucess
  */
int ls_a_flg(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_mes, char **option_tag_ls)
{
	(void) directory_to_show_ls;
	(void) option_tag_ls;

	return (ls_message_generator(read->d_name, ls_c_mes));
}

/**
  * ls_A_flg - list all files except . ..
  * @read: has the length of the arguments
  * @directory_to_show_ls: string with the name of the directory list
  * @ls_c_mes: ls complete message
  * @option_tag_ls: all option selected
  * Return: 0 on sucess
  */
int ls_A_flg(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_mes, char **option_tag_ls)
{
	(void) directory_to_show_ls;
	(void) option_tag_ls;

	if (!_strcmp(read->d_name, ".") || !_strcmp(read->d_name, ".."))
		return (0);
	return (ls_message_generator(read->d_name, ls_c_mes));
}
