#include "headerls.h"

/**
  * paste_options - paste all the info in one line
  * @ugo_permision: string with the permisions
  * @user_id: string with the name of user
  * @group_id: string with the name of group
  * @size_f_or_d: number with the size of the file
  * @time: string with the time was created
  * @d_name: string with the name of the directory
  * Return: create line with all info
  */
char *paste_options(char *ugo_permision, char *user_id, char *group_id,
	long size_f_or_d, char *time, char *d_name)
{
	char *complete_line = NULL;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c_total = 0;
	long copy_num = 0;

	c1 = count_characters(ugo_permision);
	c2 = count_characters(user_id);
	c3 = count_characters(group_id);
	c4 = count_characters(time);
	c5 = count_characters(d_name);

	c6 = 0;
	copy_num = size_f_or_d;
	while (copy_num != 0)
	{
		copy_num /= 10;
		c6++;
	}

	c_total = 5 + c1 + c2 + c3 + c4 + c5 + c6 + 2;
	complete_line = malloc(sizeof(char) * c_total);
	sprintf(complete_line, "%s %s %s %ld %s %s",
		ugo_permision, user_id, group_id, size_f_or_d, time, d_name);

	return (complete_line);
}

int free_opt_ls_l(struct dirent *read, char *file_or_directory,
	char *ugo_permision, char *time)
{
	free_memory_messages(time);
	free_memory_messages(ugo_permision);
	if (read)
		free_memory_messages(file_or_directory);
	return (0);
}

/**
  * get_more_info_dir - list the directory o file given in argv with options
  * @read: string with the name of the file listed
  * @directory_to_show_ls: string with the name of the directory list
  * Return: a complete line with the info
  */
char *get_more_info_dir(struct dirent *read, char *directory_to_show_ls)
{
	struct stat buffer = {0};
	char *file_or_directory = NULL, *d_name_d = NULL, *ugo_permision = NULL;
	char *time = NULL, *user_id = NULL, *group_id = NULL, *complet_line = NULL;
	long size_f_or_d = 0;

	if (read)
	{
		d_name_d = add_bar_diagonal_end(read->d_name);
		if (!d_name_d)
			error_malloc();
		file_or_directory = concat_two_strings(d_name_d, directory_to_show_ls);
		if (!file_or_directory)
			error_malloc();
		free_memory_messages(d_name_d);
	}
	else
		file_or_directory = directory_to_show_ls;
	if (extra_info_ls(file_or_directory, &buffer))
	{
		free_memory_messages(file_or_directory);
		return (NULL);
	}
	ugo_permision = get_ugo_permisions(&buffer);
	if (!ugo_permision)
		error_malloc();
	time = get_time_file_directory(&buffer);
	if (!time)
		error_malloc();
	size_f_or_d = get_size_file_directory(&buffer);
	user_id = get_user_id_file_directory(&buffer);
	group_id = get_group_id_file_directory(&buffer);
	if (read)
		complet_line = paste_options(ugo_permision, user_id, group_id,
			size_f_or_d, time, read->d_name);
	else
		complet_line = paste_options(ugo_permision, user_id, group_id,
			size_f_or_d, time, directory_to_show_ls);
	free_opt_ls_l(read, file_or_directory, ugo_permision, time);
	return (complet_line);
}
