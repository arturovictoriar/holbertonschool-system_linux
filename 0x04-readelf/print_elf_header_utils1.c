#include "header_elf.h"

/**
* print_elf_header - Print elf file header
* @elf_headers: Elf headers
* Return: 0 on success, 1 otherwise
*/
int print_elf_header(elf_struct_headers elf_headers)
{
	printf("ELF Header:\n");
	print_e_ident(elf_headers);
	print_e_class(elf_headers);
	print_e_data(elf_headers);
	print_e_version_d(elf_headers);
	print_e_osabi(elf_headers);
	print_e_abiversion(elf_headers);
	print_e_type(elf_headers);
	print_e_machine(elf_headers);
	print_e_version(elf_headers);
	print_e_entry(elf_headers);
	print_e_phoff(elf_headers);
	print_e_shoff(elf_headers);
	print_e_flags(elf_headers);
	print_e_ehsize(elf_headers);
	print_e_phentsize(elf_headers);
	print_e_phnum(elf_headers);
	print_e_shentsize(elf_headers);
	print_e_shnum(elf_headers);
	print_e_shstrndx(elf_headers);

	return (0);
}

/**
* print_e_ident - Print elf magic
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_ident(elf_struct_headers elf_headers)
{
	int i = 0;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%.2x ", elf_headers.e_64.e_ident[i]);
	printf("\n");

	return (0);
}

/**
* print_e_class - Print elf class
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_class(elf_struct_headers elf_headers)
{
	printf("  Class:                             ");
	switch (elf_headers.e_64.e_ident[EI_CLASS])
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
	default:
		printf("UNKNOWN\n");
		break;
	}

	return (0);
}

/**
* print_e_data - Print elf data
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_data(elf_struct_headers elf_headers)
{
	printf("  Data:                              ");
	switch (elf_headers.e_64.e_ident[EI_DATA])
	{
	case ELFDATANONE:
		printf("Unknown data format\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("UNKNOWN\n");
		break;
	}

	return (0);
}
