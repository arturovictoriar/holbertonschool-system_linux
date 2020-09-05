#include "header_elf.h"

/**
* print_e_machine - Print elf machine
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_machine(elf_struct_headers elf_headers)
{
	printf("  Machine:                           ");
	switch (elf_headers.e_64.e_machine)
	{
	case EM_NONE:
		printf("Unknown machine\n");
		break;
	case EM_M32:
		printf("AT&T WE 32100\n");
		break;
	case EM_SPARC:
		printf("Sun Microsystems SPARC\n");
		break;
	case EM_386:
		printf("Intel 80386\n");
		break;
	case EM_68K:
		printf("Motorola 68000\n");
		break;
	case EM_88K:
		printf("Motorola 88000\n");
		break;
	case EM_860:
		printf("Intel 80860\n");
		break;
	case EM_MIPS:
		printf("MIPS RS3000 (big-endian only)\n");
		break;
	case EM_PARISC:
		printf("HP/PA\n");
		break;
	case EM_SPARC32PLUS:
		printf("SPARC with enhanced instruction set\n");
		break;
	default:
		print_e_machine_1(elf_headers);
		break;
	}
	return (0);
}

/**
* print_e_machine_1 - Print elf machine
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_machine_1(elf_struct_headers elf_headers)
{
	switch (elf_headers.e_64.e_machine)
	{
	case EM_PPC:
		printf("PowerPC\n");
		break;
	case EM_PPC64:
		printf("PowerPC 64-bit\n");
		break;
	case EM_S390:
		printf("IBM S/390\n");
		break;
	case EM_ARM:
		printf("Advanced RISC Machines\n");
		break;
	case EM_SH:
		printf("Renesas SuperH\n");
		break;
	case EM_SPARCV9:
		printf("Sparc\n");
		break;
	case EM_IA_64:
		printf("Intel Itanium\n");
		break;
	case EM_X86_64:
		printf("Advanced Micro Devices X86-64\n");
		break;
	case EM_VAX:
		printf("DEC Vax\n");
		break;
	default:
		printf("UNKNOWN\n");
		break;
	}

	return (0);
}

/**
* print_e_version - Print elf version
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_version(elf_struct_headers elf_headers)
{
	printf("  Version:                           ");
	switch (elf_headers.e_64.e_version)
	{
	case EV_NONE:
		printf("Invalid\n");
		break;
	case EV_CURRENT:
		printf("0x%lx\n", (unsigned long)elf_headers.e_64.e_version);
		break;
	default:
		printf("UNKNOWN\n");
		break;
	}

	return (0);
}

/**
* print_e_entry - Print elf entry
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_entry(elf_struct_headers elf_headers)
{
	printf("  Entry point address:               ");
	if (is_64(elf_headers.e_64))
		printf("0x%lx\n", elf_headers.e_64.e_entry);
	else
		printf("0x%lx\n", (unsigned long)elf_headers.e_32.e_entry);
	return (0);
}

/**
* print_e_phoff - Print elf phoff
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_e_phoff(elf_struct_headers elf_headers)
{
	printf("  Start of program headers:          ");
	if (is_64(elf_headers.e_64))
	{
		printf("%lu (bytes into file)\n",
			(unsigned long)elf_headers.e_64.e_phoff);
	}
	else
	{
		printf("%lu (bytes into file)\n",
			(unsigned long)elf_headers.e_32.e_phoff);
	}

	return (0);
}
