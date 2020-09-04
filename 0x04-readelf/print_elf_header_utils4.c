#include "header_elf.h"

/**
* print_e_shoff - Print elf shoff
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shoff(Elf64_Ehdr e_64)
{
	printf("  Start of section headers:          ");
	printf("%lu (bytes into file)\n", (unsigned long)e_64.e_shoff);

	return (0);
}

/**
* print_e_flags - Print elf flags
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_flags(Elf64_Ehdr e_64)
{
	printf("  Flags:                             ");
	printf("0x%x\n", e_64.e_flags);

	return (0);
}

/**
* print_e_ehsize - Print elf ehsize
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_ehsize(Elf64_Ehdr e_64)
{
	printf("  Size of this header:               ");
	printf("%lu (bytes)\n", (unsigned long)e_64.e_ehsize);

	return (0);
}

/**
* print_e_phentsize - Print elf phentsize
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_phentsize(Elf64_Ehdr e_64)
{
	printf("  Size of program headers:           ");
	printf("%lu (bytes)\n", (unsigned long)e_64.e_phentsize);

	return (0);
}

/**
* print_e_phnum - Print elf phnum
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_phnum(Elf64_Ehdr e_64)
{
	printf("  Number of program headers:         ");
	printf("%lu\n", (unsigned long)e_64.e_phnum);

	return (0);
}
