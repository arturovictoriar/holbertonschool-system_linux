#include "header_elf.h"

/**
* is_elf - Check if a file is ELF
* @e_64: ELF structure
* Return: 1 on success, 0 otherwise
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
* Return: 0 on success, 1 otherwise
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
* handle_arqui_endi_file - Check is 32-64 bits, l_endian-b_endian, all files
* @elf_headers: Elf headers 64 bit
* @fd: file descriptor
* @av: arguments
* Return: 0 on 32 bits, 1 64 bits
*/
int handle_arqui_endi_file(elf_struct_headers *elf_headers, int fd, char **av)
{
	int read_lines = 0;

	if (is_64(elf_headers->e_64))
		return (1);
	lseek(fd, 0, SEEK_SET);
	read_lines = read(fd, &(elf_headers->e_32), sizeof(elf_headers->e_32));
	/*Check if it is a elf file*/
	if (sizeof(elf_headers->e_32) != read_lines)
	{
		fprintf(stderr, ERR_NOT_ELF, av[0]);
		exit(1);
	}
	return (0);
}
