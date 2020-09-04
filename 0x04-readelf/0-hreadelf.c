#include "header_elf.h"

/**
* main - Print the elf header
* @ac: number of argument
* @av: array of arguments
* Return: 0 on success, a different number otherwise
*/
int main(int ac, char **av)
{
	elf_struct_headers elf_headers;
	char *file_name = NULL;
	int fd = 0, read_lines = 0;

	if (ac != 2)
	{
		fprintf(stderr, ERR_USAGE);
		exit(1);
	}

	/*Clean the elf variable to 0*/
	memset(&elf_headers, 0, sizeof(elf_headers));
	file_name = av[1];
	/*Open the posible elf file*/
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			fprintf(stderr, ERR_FILE_NOT_FOUND, av[0], file_name);
		else if (errno == EACCES)
			fprintf(stderr, ERR_NOT_READ, av[0], file_name);
		exit(1);
	}

	read_lines = read(fd, &elf_headers.e_64, sizeof(elf_headers.e_64));
	/*Check if it is a elf file*/
	if (read_lines != sizeof(elf_headers.e_64) || !is_elf(elf_headers.e_64))
	{
		fprintf(stderr, ERR_NOT_ELF, av[0]);
		exit(1);
	}

	print_elf_header(elf_headers);
	return (0);
}
