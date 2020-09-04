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
* print_elf_header - Print elf file header
* @elf_headers: Elf headers
* Return: 0 on success, 1 otherwise
*/
int print_elf_header(elf_struct_headers elf_headers)
{
	printf("ELF Header:\n");
	print_e_ident(elf_headers.e_64);
	print_e_class(elf_headers.e_64);
	print_e_data(elf_headers.e_64);
	print_e_version_d(elf_headers.e_64);
	print_e_osabi(elf_headers.e_64);
	print_e_abiversion(elf_headers.e_64);
	print_e_type(elf_headers.e_64);
	print_e_machine(elf_headers.e_64);
	print_e_version(elf_headers.e_64);
	print_e_entry(elf_headers.e_64);
	print_e_phoff(elf_headers.e_64);
	print_e_shoff(elf_headers.e_64);
	print_e_flags(elf_headers.e_64);
	print_e_ehsize(elf_headers.e_64);
	print_e_phentsize(elf_headers.e_64);
	print_e_phnum(elf_headers.e_64);
	print_e_shentsize(elf_headers.e_64);
	print_e_shnum(elf_headers.e_64);
	print_e_shstrndx(elf_headers.e_64);

	return (0);
}

/**
* print_e_ident - Print elf magic
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_ident(Elf64_Ehdr e_64)
{
	int i = 0;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", e_64.e_ident[i]);
	printf("\n");

	return (0);
}

/**
* print_e_class - Print elf class
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_class(Elf64_Ehdr e_64)
{
	printf("  Class:                             ");
	switch (e_64.e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("INVALID\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	}

	return (0);
}

/**
* print_e_data - Print elf data
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_data(Elf64_Ehdr e_64)
{
	printf("  Data:                              ");
	switch (e_64.e_ident[EI_DATA])
	{
	case ELFDATANONE:
		printf("Unknown data format\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big-endian\n");
		break;
	}

	return (0);
}
