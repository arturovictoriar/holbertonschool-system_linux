#include "_getline.h"

/**
 * free_static_var - entry point.
 * @all_text_read_fd: All lines for all fds
 * @all_fds: All fds
 * @all_buff_fd: All buffer for all fds
 * @num_fds: Numbers of fds
 * Return: always -1.
 */
int free_static_var(char ***all_text_read_fd, int ***all_fds,
	char ***all_buff_fd, int *num_fds)
{
	int index = 0;

	if (!(*all_text_read_fd) && !(*all_fds) && !(*all_buff_fd) && !(*num_fds))
		return (-1);
	for (index = 0; index < *num_fds; index++)
	{
		free((*all_text_read_fd)[index]);
		(*all_text_read_fd)[index] = NULL;
		free((*all_fds)[index]);
		(*all_fds)[index] = NULL;
		free((*all_buff_fd)[index]);
		(*all_buff_fd)[index] = NULL;
	}
	free(*all_text_read_fd);
	*all_text_read_fd = NULL;
	free(*all_fds);
	*all_fds = NULL;
	free(*all_buff_fd);
	*all_buff_fd = NULL;

	*num_fds = 0;
	return (-1);
}

/**
 * realloc_all_text_fd - entry point.
 * @all_text_fd: All lines for all fds
 * @all_fds: All fds
 * @all_buff_fd: All buffer for all fds
 * @num_fds: Numbers of fds
 * @num_fds_plus: Numbers of fds plus one
 * Return: 1 on success otherwise 0.
 */
int realloc_all_text_fd(char ***all_text_fd, int ***all_fds,
	char ***all_buff_fd, int num_fds, int num_fds_plus)
{
	int index = 0;
	int **new_all_fds = NULL;
	char **new_all_text_fd = NULL, **new_all_buf_fd;

	new_all_fds = malloc(sizeof(int *) * num_fds_plus);
	if (!new_all_fds)
		return (0);
	for (index = 0; index < num_fds; index++)
		new_all_fds[index] = (*all_fds)[index];
	new_all_fds[index] = NULL;

	new_all_text_fd = malloc(sizeof(char *) * num_fds_plus);
	if (!new_all_text_fd)
	{
		free(new_all_fds);
		return (0);
	}
	for (index = 0; index < num_fds; index++)
		new_all_text_fd[index] = (*all_text_fd)[index];
	new_all_text_fd[index] = NULL;

	new_all_buf_fd = malloc(sizeof(char *) * num_fds_plus);
	if (!new_all_text_fd)
	{
		free(new_all_fds);
		free(new_all_text_fd);
		return (0);
	}
	for (index = 0; index < num_fds; index++)
		new_all_buf_fd[index] = (*all_buff_fd)[index];
	new_all_buf_fd[index] = NULL;

	free(*all_fds);
	(*all_fds) = new_all_fds;
	free(*all_text_fd);
	(*all_text_fd) = new_all_text_fd;
	free(*all_buff_fd);
	(*all_buff_fd) = new_all_buf_fd;

	return (1);
}

/**
 * num_fds_realloc - entry point.
 * @all_text_fd: All lines for all fds
 * @all_fds: All fds
 * @all_buff_fd: All buffer for all fds
 * @num_fds: Numbers of fds
 * @fd: Fd id
 * Return: a positive number on sucess always -1.
 */
int num_fds_realloc(char ***all_text_fd, int ***all_fds, char ***all_buff_fd,
	int *num_fds, int fd)
{
	int *new_fd_num = NULL, index = 0;

	if (fd == -1)
		return (free_static_var(all_text_fd, all_fds, all_buff_fd, num_fds));
	for (index = 0; index < *num_fds; index++)
		if ((*all_fds)[index][0] == fd)
			return (index);
	if (!(*num_fds))
	{
		(*all_text_fd) = malloc(sizeof(char *) * 1);
		if (!(*all_text_fd))
			return (-1);
		(*all_fds) = malloc(sizeof(int *) * 1);
		if (!(*all_fds))
		{
			free(*all_text_fd);
			*all_text_fd = NULL;
			return (-1);
		}
		(*all_buff_fd) = malloc(sizeof(char *) * 1);
		if (!(*all_buff_fd))
		{
			free(*all_text_fd);
			*all_text_fd = NULL;
			free(*all_fds);
			*all_fds = NULL;
			return (-1);
		}
		(*all_text_fd)[0] = NULL;
		(*all_fds)[0] = NULL;
		(*all_buff_fd)[0] = NULL;
	}
	else if (!realloc_all_text_fd(all_text_fd, all_fds, all_buff_fd, *num_fds,
		*num_fds + 1))
		return (-1);
	new_fd_num = malloc(sizeof(int) * 3);
	if (!new_fd_num)
		return (-1);
	new_fd_num[0] = fd;
	new_fd_num[1] = 0;
	new_fd_num[2] = 0;
	(*all_fds)[*num_fds] = new_fd_num;
	(*num_fds) = (*num_fds) + 1;
	return (*num_fds - 1);
}

/**
 * set_new_line - entry point.
 * @all_text_fd: All lines for all fds
 * @all_fds: All fds
 * @all_buff_fd: All buffer for all fds
 * @fd_pos: Position in the array of the fd
 * @b: current buffer of the read fucntion
 * @l_jum: last potision + 1 of the new line char
 * @i_buff: position of the new line char
 * @r: Number of characters read
 * Return: always 0.
 */
int set_new_line(char **all_text_fd, int **all_fds, char **all_buff_fd,
	int fd_pos, char *b, int l_jum, int i_buff, int r)
{
	char *new_mes = NULL;
	int len_message = 0;

	if (!all_text_fd[fd_pos])
	{
		new_mes = malloc(sizeof(char) * (i_buff - l_jum + 1));
		if (!new_mes)
			return (1);
		strncpy(new_mes, &(b[l_jum]), (i_buff - l_jum));
		new_mes[i_buff - l_jum] = '\0';
		all_text_fd[fd_pos] = new_mes;
	}
	else
	{
		for (len_message = 0; all_text_fd[fd_pos][len_message] != '\0';
			len_message++)
			continue;
		new_mes = malloc(sizeof(char) * (len_message + i_buff - l_jum + 1));
		if (!new_mes)
			return (1);
		strcpy(new_mes, all_text_fd[fd_pos]);
		strncpy(&(new_mes[len_message]), &(b[l_jum]), (i_buff - l_jum));
		new_mes[len_message + i_buff - l_jum] = '\0';
		free(all_text_fd[fd_pos]);
		all_text_fd[fd_pos] = new_mes;
	}
	if (i_buff + 1 >= r)
	{
		if (all_buff_fd[fd_pos])
		{
			free(all_buff_fd[fd_pos]);
			all_buff_fd[fd_pos] = NULL;
		}
		all_fds[fd_pos][1] = 0;
		all_fds[fd_pos][2] = 0;
		return (0);
	}
	if (!all_buff_fd[fd_pos])
	{
		all_buff_fd[fd_pos] = b;
		all_fds[fd_pos][2] = r;
	}
	all_fds[fd_pos][1] = i_buff + 1;
	return (0);
}

/**
 * _getline - entry point.
 * @fd: file descriptor id
 * Return: a string pointer on succes otherwise NULL.
 */
char *_getline(const int fd)
{
	static char **all_text_fd, **all_buff_fd;
	static int **all_fds, num_fds;
	int fd_pos = -1, r = 0, i_buff = 0;
	char *b = NULL;

	fd_pos = num_fds_realloc(&all_text_fd, &all_fds, &all_buff_fd, &num_fds,
		(int) fd);
	if (fd_pos == -1)
		return (NULL);
	if (all_buff_fd[fd_pos])
	{
		b = all_buff_fd[fd_pos];
		r = all_fds[fd_pos][2];
		all_text_fd[fd_pos] = NULL;
		for (i_buff = all_fds[fd_pos][1]; i_buff < all_fds[fd_pos][2];
			i_buff++)
		{
			if (b[i_buff] == '\n')
			{
				set_new_line(all_text_fd, all_fds, all_buff_fd, fd_pos, b,
					all_fds[fd_pos][1], i_buff, r);
				return (all_text_fd[fd_pos]);
			}
		}
		set_new_line(all_text_fd, all_fds, all_buff_fd, fd_pos, b,
			all_fds[fd_pos][1], i_buff, r);
	}
	b = malloc(sizeof(char) * (READ_SIZE));
	if (!b)
		return (NULL);
	for (r = read(fd, b, READ_SIZE); r > 0; r = read(fd, b, READ_SIZE))
	{
		for (i_buff = 0; i_buff < r; i_buff++)
		{
			if (b[i_buff] == '\n')
			{
				set_new_line(all_text_fd, all_fds, all_buff_fd, fd_pos, b,
					0, i_buff, r);
				return (all_text_fd[fd_pos]);
			}
		}
		set_new_line(all_text_fd, all_fds, all_buff_fd, fd_pos, b, 0, i_buff,
			r);
	}
	free(b);
	return (NULL);
}