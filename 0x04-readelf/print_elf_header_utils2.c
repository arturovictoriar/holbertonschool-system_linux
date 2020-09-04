#include "header_elf.h"

/**
* print_e_version_d - Print elf version decimal number
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_version_d(Elf64_Ehdr e_64)
{
	printf("  Version:                           ");
	switch (e_64.e_ident[EI_VERSION])
	{
	case EV_NONE:
		printf("Invalid\n");
		break;
	case EV_CURRENT:
		printf("%x (current)\n", e_64.e_ident[EI_VERSION]);
		break;
	}

	return (0);
}

/**
* print_e_osabi - Print elf osabi
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_osabi(Elf64_Ehdr e_64)
{
	printf("  OS/ABI:                            ");
	switch (e_64.e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("TRU64 UNIX\n");
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
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_abiversion(Elf64_Ehdr e_64)
{
	switch (e_64.e_ident[EI_ABIVERSION])
	{
	case 0x00:
		printf("  ABI Version:                       %d\n",
			   e_64.e_ident[EI_ABIVERSION]);
		break;
	}

	return (0);
}

/**
* print_e_type - Print elf type
* @e_64: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_type(Elf64_Ehdr e_64)
{
	printf("  Type:                              ");
	switch (e_64.e_type)
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
	}

	return (0);
}
