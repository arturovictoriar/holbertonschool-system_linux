#include "header_elf.h"

/**
* get_elf_program_flag_64 - Get elf program flag 64
* @elf_headers: Elf headers
* @i: index
* Return: the flags
*/
char *get_elf_program_flag_64(elf_struct_headers *elf_headers, unsigned int i)
{
	static char str[4];

	if (elf_headers->ep_64[i].p_flags & PF_R)
		str[0] = 'R';
	else
		str[0] = ' ';

	if (elf_headers->ep_64[i].p_flags & PF_W)
		str[1] = 'W';
	else
		str[1] = ' ';

	if (elf_headers->ep_64[i].p_flags & PF_X)
		str[2] = 'E';
	else
		str[2] = ' ';

	str[3] = 0;

	return (str);
}

/**
* get_elf_program_flag_32 - Get elf program flag 32
* @elf_headers: Elf headers
* @i: index
* Return: the flags
*/
char *get_elf_program_flag_32(elf_struct_headers *elf_headers, unsigned int i)
{
	static char str[4];

	if (elf_headers->ep_32[i].p_flags & PF_R)
		str[0] = 'R';
	else
		str[0] = ' ';

	if (elf_headers->ep_32[i].p_flags & PF_W)
		str[1] = 'W';
	else
		str[1] = ' ';

	if (elf_headers->ep_32[i].p_flags & PF_X)
		str[2] = 'E';
	else
		str[2] = ' ';

	str[3] = 0;

	return (str);
}

/**
* get_elf_program_type_64 - Get elf program type 64
* @elf_headers: Elf headers
* @i: index
* Return: the type
*/
char *get_elf_program_type_64(elf_struct_headers *elf_headers, unsigned int i)
{
	switch (elf_headers->ep_64[i].p_type)
	{
	case PT_NULL:
		return ("NULL");
	case PT_LOAD:
		return ("LOAD");
	case PT_DYNAMIC:
		return ("DYNAMIC");
	case PT_INTERP:
		return ("INTERP");
	case PT_NOTE:
		return ("NOTE");
	case PT_SHLIB:
		return ("SHLIB");
	case PT_PHDR:
		return ("PHDR");
	case PT_TLS:
		return ("TLS");
	case PT_GNU_EH_FRAME:
		return ("GNU_EH_FRAME");
	case PT_GNU_STACK:
		return ("GNU_STACK");
	case PT_GNU_RELRO:
		return ("GNU_RELRO");
	case 0x6464E550:
		return ("LOOS+464e550");
	default:
		return ("UNKNOWN");
	}
}

/**
* get_elf_program_type_32 - Get elf program type 32
* @elf_headers: Elf headers
* @i: index
* Return: the type
*/
char *get_elf_program_type_32(elf_struct_headers *elf_headers, unsigned int i)
{
	switch (elf_headers->ep_32[i].p_type)
	{
	case PT_NULL:
		return ("NULL");
	case PT_LOAD:
		return ("LOAD");
	case PT_DYNAMIC:
		return ("DYNAMIC");
	case PT_INTERP:
		return ("INTERP");
	case PT_NOTE:
		return ("NOTE");
	case PT_SHLIB:
		return ("SHLIB");
	case PT_PHDR:
		return ("PHDR");
	case PT_TLS:
		return ("TLS");
	case PT_GNU_EH_FRAME:
		return ("GNU_EH_FRAME");
	case PT_GNU_STACK:
		return ("GNU_STACK");
	case PT_GNU_RELRO:
		return ("GNU_RELRO");
	case 0x6464E550:
		return ("LOOS+464e550");
	default:
		return ("UNKNOWN");
	}
}

/**
* get_segment_resides - Get where the segment resides
* @elf_headers: Elf headers
* @fd: file descriptor
* @i: index
* @str: string with the name of segement resides
* Return: the type
*/
int *get_segment_resides(elf_struct_headers *elf_headers, int fd,
	unsigned int i, char **str)
{
	unsigned int read_lines = 0;

	if (is_64(elf_headers->e_64))
	{
		*str = malloc(sizeof(char) * elf_headers->ep_64[i].p_memsz);
		if (!*str)
			return (NULL);
		lseek(fd, elf_headers->ep_64[i].p_offset, SEEK_SET);
		read_lines = read(fd, *str, elf_headers->ep_64[i].p_memsz);
		if (elf_headers->ep_64[i].p_memsz != read_lines)
			exit(1);
	}
	else
	{
		*str = malloc(sizeof(char) * elf_headers->ep_32[i].p_memsz);
		if (!*str)
			return (NULL);
		lseek(fd, elf_headers->ep_32[i].p_offset, SEEK_SET);
		read_lines = read(fd, *str, elf_headers->ep_32[i].p_memsz);
		if (elf_headers->ep_32[i].p_memsz != read_lines)
			exit(1);
	}

	return (0);
}
