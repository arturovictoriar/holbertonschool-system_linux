#include "header_elf.h"

/**
* is_elf - Check if a file is ELF
* @e_64: ELF structure
* Return: 1 elf file, 0 otherwise
*/
int is_elf(Elf64_Ehdr e_64)
{
	if (e_64.e_ident[EI_MAG0] == ELFMAG0 &&
		e_64.e_ident[EI_MAG1] == ELFMAG1 &&
		e_64.e_ident[EI_MAG2] == ELFMAG2 &&
		e_64.e_ident[EI_MAG3] == ELFMAG3)
		return (1);
	return (0);
}

/**
* is_64 - Check is the file is 64 bits
* @e_64: Elf headers 64 bit
* Return: 1, for 64 bits, 0, for 32 bits
*/
int is_64(Elf64_Ehdr e_64)
{
	switch (e_64.e_ident[EI_CLASS])
	{
	case ELFCLASS32:
		return (0);
	case ELFCLASS64:
		return (1);
	default:
		fprintf(stderr, "No Arquitect found\n");
		exit(1);
	}

	return (0);
}

/**
* is_little_endian - Check is the file is little endian
* @e_64: Elf headers 64 bit
* Return: 1, for little endian, 0 for big endian
*/
int is_little_endian(Elf64_Ehdr e_64)
{
	switch (e_64.e_ident[EI_DATA])
	{
	case ELFDATA2LSB:
		return (1);
	case ELFDATA2MSB:
		return (0);
	default:
		fprintf(stderr, "No Data format found\n");
		exit(1);
	}

	return (0);
}

/**
* handle_data_format - Convert little to big endian if elf is b_endian
* @elf_headers: Elf headers
* Return: 1 succed, 0 otherwise
*/
int handle_data_format(elf_struct_headers *elf_headers)
{
	if (is_little_endian(elf_headers->e_64))
		return (0);
	convert_little_to_big_end_64(elf_headers);
	return (1);
}

/**
* handle_arquitec - Check is 32-64 bits, l_endian-b_endian, all files
* @elf_headers: Elf headers 64 bit
* @fd: file descriptor
* @av: arguments
* Return: 0 on 32 bits, 1 on 64 bits
*/
int handle_arquitec(elf_struct_headers *elf_headers, int fd, char **av)
{
	int read_lines = 0;

	if (is_64(elf_headers->e_64))
		return (0);
	lseek(fd, 0, SEEK_SET);
	read_lines = read(fd, &(elf_headers->e_32), sizeof(elf_headers->e_32));
	/*Check if it is a elf file*/
	if (sizeof(elf_headers->e_32) != read_lines)
	{
		fprintf(stderr, ERR_NOT_ELF, av[0]);
		exit(1);
	}
	return (1);
}
