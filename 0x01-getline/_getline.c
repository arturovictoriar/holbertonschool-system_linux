#include "_getline.h"

char *free_static_var(char ***all_text_read_fd, int ***all_fds, int *num_fds)
{
	int index = 0;

	if (!(*all_text_read_fd) && !(*all_fds) && !(*num_fds))
		return (NULL);
	for (index = 0; index < *num_fds; index++)
	{
		free((*all_text_read_fd)[index]);
		(*all_text_read_fd)[index] = NULL;
		free((*all_fds)[index]);
		(*all_fds)[index] = NULL;
	}
	free(*all_text_read_fd);
	*all_text_read_fd = NULL;
	free(*all_fds);
	*all_fds = NULL;

	*num_fds = 0;
	return (NULL);
}

int realloc_all_text_fd(char ***all_text_fd, int ***all_fds, int num_fds,
						int num_fds_plus)
{
	int index = 0;
	int **new_all_fds = NULL;
	char **new_all_text_fd = NULL;

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

	free(*all_fds);
	(*all_fds) = new_all_fds;
	free(*all_text_fd);
	(*all_text_fd) = new_all_text_fd;

	return (1);
}

int num_fds_realloc(char ***all_text_fd, int ***all_fds, int *num_fds, int fd)
{
	int *new_fd_num = NULL;

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
		(*all_text_fd)[0] = NULL;
		(*all_fds)[0] = NULL;
	}
	else if (!realloc_all_text_fd(all_text_fd, all_fds, *num_fds, *num_fds + 1))
		return (-1);

	new_fd_num = malloc(sizeof(int) * 2);
	new_fd_num[0] = fd;
	new_fd_num[1] = 0;
	(*all_fds)[*num_fds] = new_fd_num;

	(*num_fds) = (*num_fds) + 1;
	return (*num_fds - 1);
}

int set_new_line(char **all_text_fd, int fd_pos, char *b, int l_jum,
	int i_buff)
{
	char *new_message = NULL;
	int len_message = 0;

	if (!all_text_fd[fd_pos])
	{
		new_message = malloc(sizeof(char) * (i_buff - l_jum + 1));
		if (!new_message)
			return (1);
		strncpy(new_message, &(b[l_jum]), (i_buff - l_jum));
		new_message[i_buff - l_jum] = '\0';
		free(all_text_fd[fd_pos]);
		all_text_fd[fd_pos] = new_message;
		return (0);
	}

	for (len_message = 0; all_text_fd[fd_pos][len_message] != '\0'; len_message++)
		continue;

	new_message = malloc(sizeof(char) * (len_message + i_buff - l_jum + 1));
	if (!new_message)
		return (1);
	strcpy(new_message, all_text_fd[fd_pos]);
	strncpy(&(new_message[len_message]), &(b[l_jum]), (i_buff - l_jum));
	new_message[i_buff - l_jum] = '\0';
	free(all_text_fd[fd_pos]);
	all_text_fd[fd_pos] = new_message;
	return (0);
}

char *_getline(const int fd)
{
	static char **all_text_fd = NULL;
	static int **all_fds = NULL;
	static int num_fds = 0;
	int index = 0, fd_pos = -1, r = 0, i_buff = 0, l_buff = 0, l_jum = 0;
	char *b = NULL;

	if (fd == -1)
		return (free_static_var(&all_text_fd, &all_fds, &num_fds));
	for (index = 0; index < num_fds; index++)
		if (all_fds[index][0] == fd)
			fd_pos = index;
	if (fd_pos < 0)
		fd_pos = num_fds_realloc(&all_text_fd, &all_fds, &num_fds, (int)fd);
	if (fd_pos == -1)
		return (NULL);
	
	b = malloc(sizeof(char) * (READ_SIZE));
	if (!b)
		return (NULL);
	for (r = read(fd, b, READ_SIZE); r > 0; r = read(fd, b, READ_SIZE))
	{
		l_jum = 0;
		for (i_buff = 0; i_buff < r; i_buff++)
		{
			if (b[i_buff] == '\n')
			{
				if (l_buff >= all_fds[fd_pos][1])
				{
					set_new_line(all_text_fd, fd_pos, b, l_jum, i_buff);
					all_fds[fd_pos][1]++;
					free(b);
					return (all_text_fd[fd_pos]);
				}
				l_jum += i_buff + 1;
				l_buff++;
			}
		}
		set_new_line(all_text_fd, fd_pos, b, l_jum, i_buff);
	}
	free(b);
	return (NULL);
}