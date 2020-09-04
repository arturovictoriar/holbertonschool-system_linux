#include "header_elf.h"

/**
* print_e_shoff - Print elf shoff
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_shoff(elf_struct_headers elf_headers)
{
	printf("  Start of section headers:          ");
	if (is_64(elf_headers.e_64))
	{
		printf("%lu (bytes into file)\n",
			(unsigned long)elf_headers.e_64.e_shoff);
	}
	else
	{
		printf("%lu (bytes into file)\n",
			(unsigned long)elf_headers.e_32.e_shoff);
	}

	return (0);
}

/**
* print_e_flags - Print elf flags
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_flags(elf_struct_headers elf_headers)
{
	printf("  Flags:                             ");
	if (is_64(elf_headers.e_64))
		printf("0x%lx\n", (unsigned long)elf_headers.e_64.e_flags);
	else
		printf("0x%lx\n", (unsigned long)elf_headers.e_32.e_flags);

	return (0);
}

/**
* print_e_ehsize - Print elf ehsize
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_ehsize(elf_struct_headers elf_headers)
{
	printf("  Size of this header:               ");
	if (is_64(elf_headers.e_64))
		printf("%ld (bytes)\n", (long)elf_headers.e_64.e_ehsize);
	else
		printf("%ld (bytes)\n", (long)elf_headers.e_32.e_ehsize);

	return (0);
}

/**
* print_e_phentsize - Print elf phentsize
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_phentsize(elf_struct_headers elf_headers)
{
	printf("  Size of program headers:           ");
	if (is_64(elf_headers.e_64))
		printf("%ld (bytes)\n", (long)elf_headers.e_64.e_phentsize);
	else
		printf("%ld (bytes)\n", (long)elf_headers.e_32.e_phentsize);

	return (0);
}

/**
* print_e_phnum - Print elf phnum
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_phnum(elf_struct_headers elf_headers)
{
	printf("  Number of program headers:         ");
	if (is_64(elf_headers.e_64))
		printf("%ld\n", (long)elf_headers.e_64.e_phnum);
	else
		printf("%ld\n", (long)elf_headers.e_32.e_phnum);

	return (0);
}
