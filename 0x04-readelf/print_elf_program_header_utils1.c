#include "header_elf.h"

/**
* print_elf_program_header - Print elf file header
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_elf_program_header(elf_struct_headers *elf_headers, int fd)
{
	if ((is_64(elf_headers->e_64) && !elf_headers->e_64.e_phnum) ||
		(!is_64(elf_headers->e_64) && !elf_headers->e_32.e_phnum))
	{
		printf("\nThere are no program headers in this file.\n");
		return (1);
	}
	print_program_type_entry(elf_headers);
	if (is_64(elf_headers->e_64))
		printf("There are %d program headers, starting at offset %ld\n",
			   elf_headers->e_64.e_phnum, elf_headers->e_64.e_phoff);
	else
		printf("There are %d program headers, starting at offset %ld\n",
			   elf_headers->e_32.e_phnum,
			   (unsigned long)elf_headers->e_32.e_phoff);
	handle_program_header(elf_headers, fd);
	handle_section_header(elf_headers, fd), printf("\nProgram Headers:\n");
	handle_format_and_print_program(elf_headers, fd);
	print_segment_section(elf_headers, fd);
	return (0);
}

/**
* print_program_type_entry - Print elf type
* @elf_headers: Elf headers 64 bit
* Return: 0 on success, 1 otherwise
*/
int print_program_type_entry(elf_struct_headers *elf_headers)
{
	printf("\nElf file type is ");
	switch (elf_headers->e_64.e_type)
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
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("UNKNOWN\n");
		break;
	}

	printf("Entry point ");
	if (is_64(elf_headers->e_64))
		printf("0x%lx\n", elf_headers->e_64.e_entry);
	else
		printf("0x%lx\n", (unsigned long)elf_headers->e_32.e_entry);

	return (0);
}

/**
* print_64_program - Print elf section program 64
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_64_program(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0;
	char *str = NULL;

	/*char *str_table = NULL; str_table = get_string_table(elf_headers, fd);*/
	printf("  Type           Offset   VirtAddr           ");
	printf("PhysAddr           FileSiz  MemSiz   Flg Align\n");
	for (i = 0; i < elf_headers->e_64.e_phnum; i++)
	{
		printf("  %-14s 0x%6.6lx 0x%16.16lx 0x%16.16lx 0x%6.6lx",
			   get_elf_program_type_64(elf_headers, i),
			   elf_headers->ep_64[i].p_offset,
			   elf_headers->ep_64[i].p_vaddr,
			   elf_headers->ep_64[i].p_paddr,
			   elf_headers->ep_64[i].p_filesz);
		printf(" 0x%6.6lx %s %#lx\n",
			   elf_headers->ep_64[i].p_memsz,
			   get_elf_program_flag_64(elf_headers, i),
			   elf_headers->ep_64[i].p_align);

		if (elf_headers->ep_64[i].p_type == PT_INTERP)
		{
			get_segment_resides(elf_headers, fd, i, &str);
			printf("      [Requesting program interpreter: %s]\n", str);
			if (str)
				free(str);
		}
	}
	return (0);
}

/**
* print_32_program - Print elf program header 32
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_32_program(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0;
	char *str = NULL;

	/*char *str_table = NULL; str_table = get_string_table(elf_headers, fd);*/
	printf("  Type           Offset   VirtAddr   PhysAddr");
	printf("   FileSiz MemSiz  Flg Align\n");
	for (i = 0; i < elf_headers->e_32.e_phnum; i++)
	{
		printf("  %-14s 0x%6.6lx 0x%8.8lx 0x%8.8lx 0x%5.5lx",
			   get_elf_program_type_32(elf_headers, i),
			   (unsigned long)elf_headers->ep_32[i].p_offset,
			   (unsigned long)elf_headers->ep_32[i].p_vaddr,
			   (unsigned long)elf_headers->ep_32[i].p_paddr,
			   (unsigned long)elf_headers->ep_32[i].p_filesz);
		printf(" 0x%5.5lx %s %#lx\n",
			   (unsigned long)elf_headers->ep_32[i].p_memsz,
			   get_elf_program_flag_32(elf_headers, i),
			   (unsigned long)elf_headers->ep_32[i].p_align);

		if (elf_headers->ep_32[i].p_type == PT_INTERP)
		{
			get_segment_resides(elf_headers, fd, i, &str);
			printf("      [Requesting program interpreter: %s]\n", str);
			if (str)
				free(str);
		}
	}
	/*free(str_table);*/
	return (0);
}

/**
* print_segment_section - Print section segment
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_segment_section(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0, j = 0;
	char *str_table = NULL;

	str_table = get_string_table(elf_headers, fd);
	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	if (is_64(elf_headers->e_64))
	{
		for (i = 0; i < elf_headers->e_64.e_phnum; i++)
		{
			printf("   %.2u     ", i);
			for (j = 0; j < elf_headers->e_64.e_shnum; j++)
			{
				if (get_section_program_64_32(elf_headers, i, j))
					printf("%s ", &str_table[elf_headers->es_64[j].sh_name]);
			}
			printf("\n");
		}
	}
	else
	{
		for (i = 0; i < elf_headers->e_32.e_phnum; i++)
		{
			printf("   %.2u     ", i);
			for (j = 0; j < elf_headers->e_32.e_shnum; j++)
			{
				if (get_section_program_64_32(elf_headers, i, j))
					printf("%s ", &str_table[elf_headers->es_32[j].sh_name]);
			}
			printf("\n");
		}
	}
	free(str_table);
	return (0);
}
