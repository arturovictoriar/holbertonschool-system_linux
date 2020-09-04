#include "header_elf.h"

/**
* print_e_shentsize - Print elf shentsize
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shentsize(elf_struct_headers elf_headers)
{
	printf("  Size of section headers:           ");
	if (is_64(elf_headers.e_64))
		printf("%lu (bytes)\n", (unsigned long)elf_headers.e_64.e_shentsize);
	else
		printf("%lu (bytes)\n", (unsigned long)elf_headers.e_32.e_shentsize);

	return (0);
}

/**
* print_e_shnum - Print elf shnum
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shnum(elf_struct_headers elf_headers)
{
	printf("  Number of section headers:         ");
	if (is_64(elf_headers.e_64))
		printf("%ld\n", (long)elf_headers.e_64.e_shnum);
	else
		printf("%ld\n", (long)elf_headers.e_32.e_shnum);

	return (0);
}

/**
* print_e_shstrndx - Print elf shstrndx
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shstrndx(elf_struct_headers elf_headers)
{
	printf("  Section header string table index: ");
	if (is_64(elf_headers.e_64))
		printf("%ld\n", (long)elf_headers.e_64.e_shstrndx);
	else
		printf("%ld\n", (long)elf_headers.e_32.e_shstrndx);

	return (0);
}
