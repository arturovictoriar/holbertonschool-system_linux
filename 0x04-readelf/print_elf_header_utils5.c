#include "header_elf.h"

/**
* print_e_shentsize - Print elf shentsize
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shentsize(Elf64_Ehdr e_64)
{
	printf("  Size of section headers:           ");
	printf("%lu (bytes)\n", (unsigned long)e_64.e_shentsize);

	return (0);
}

/**
* print_e_shnum - Print elf shnum
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shnum(Elf64_Ehdr e_64)
{
	printf("  Number of section headers:         ");
	printf("%lu\n", (unsigned long)e_64.e_shnum);

	return (0);
}

/**
* print_e_shstrndx - Print elf shstrndx
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shstrndx(Elf64_Ehdr e_64)
{
	printf("  Section header string table index: ");
	printf("%lu\n", (unsigned long)e_64.e_shstrndx);

	return (0);
}
