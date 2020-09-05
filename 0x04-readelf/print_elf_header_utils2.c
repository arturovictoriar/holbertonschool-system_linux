#include "header_elf.h"

/**
* print_e_version_d - Print elf version decimal number
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_version_d(elf_struct_headers elf_headers)
{
	printf("  Version:                           ");
	switch (elf_headers.e_64.e_ident[EI_VERSION])
	{
	case EV_NONE:
		printf("Invalid\n");
		break;
	case EV_CURRENT:
		printf("%x (current)\n", elf_headers.e_64.e_ident[EI_VERSION]);
		break;
	}

	return (0);
}

/**
* print_e_osabi - Print elf osabi
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_osabi(elf_struct_headers elf_headers)
{
	printf("  OS/ABI:                            ");
	switch (elf_headers.e_64.e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM architecture\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Stand-alone (embedded)\n");
		break;
	}

	return (0);
}

/**
* print_e_abiversion - Print elf osabi version
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_abiversion(elf_struct_headers elf_headers)
{
	printf("  ABI Version:                       %d\n",
		elf_headers.e_64.e_ident[EI_ABIVERSION]);
	return (0);
}

/**
* print_e_type - Print elf type
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_type(elf_struct_headers elf_headers)
{
	printf("  Type:                              ");
	switch (elf_headers.e_64.e_type)
	{
	case ET_NONE:
		printf("NONE (Unknown type)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("UNKNOWN\n");
		break;
	}

	return (0);
}
