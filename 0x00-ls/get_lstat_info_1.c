#include "headerls.h"

/**
  * get_user_id_file_directory - get the id user of a file or directory
  * @buffer: structure with the info state
  * Return: string with the id user
  */
char *get_user_id_file_directory(struct stat *buffer)
{
	char *usr_id = NULL;

	usr_id = getpwuid(buffer->st_uid)->pw_name;
	return (usr_id);
}

/**
  * get_group_id_file_directory - get the id group of a file or directory
  * @buffer: structure with the info state
  * Return: string with the id group
  */
char *get_group_id_file_directory(struct stat *buffer)
{
	char *grp_id = NULL;

	grp_id = getgrgid(buffer->st_gid)->gr_name;
	return (grp_id);
}
