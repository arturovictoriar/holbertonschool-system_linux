#include "header_elf.h"

/**
* _hnm - Print a symbol table
* @prg: program name
* @file_name: file name
* Return: 0 on success, a different number otherwise
*/
int _hnm(char *prg, char *file_name)
{
	elf_struct_headers elf_headers;
	int fd = 0, read_lines = 0;

	/*Clean the elf variable to 0*/
	memset(&elf_headers, 0, sizeof(elf_headers));
	/*Open the posible elf file*/
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			fprintf(stderr, ERR_FILE_NOT_FOUND, prg, file_name);
		else if (errno == EACCES)
			fprintf(stderr, ERR_NOT_READ, prg, file_name);
		exit(1);
	}

	read_lines = read(fd, &elf_headers.e_64, sizeof(elf_headers.e_64));
	/*Check if it is a elf file*/
	if (sizeof(elf_headers.e_64) != read_lines || !is_elf(elf_headers.e_64))
	{
		fprintf(stderr, ERR_NOT_ELF, prg);
		exit(1);
	}

	handle_arquitec(&elf_headers, fd, prg);
	handle_data_format(&elf_headers);
	if (print_elf_symbol_header(&elf_headers, fd))
		fprintf(stderr, "%s: %s: no symbols\n", prg, file_name);
	clean_symbol_64_32(&elf_headers);
	close(fd);
	return (0);
}

/**
* main - Print the symbol tables
* @ac: number of argument
* @av: array of arguments
* Return: 0 on success, a different number otherwise
*/
int main(int ac, char **av)
{
	unsigned int i = 0;

	if (ac < 2)
	{
		fprintf(stderr, ERR_USAGE);
		exit(1);
	}

	for (i = 1; av[i]; i++)
	{
		if (ac > 2)
			printf("\n%s:\n", av[i]);
		_hnm(av[0], av[i]);
	}

	return (0);
}
