#include "header_elf.h"

/**
* print_elf_section_header - Print elf file header
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_elf_section_header(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0;

	if (is_64(elf_headers->e_64) && !elf_headers->e_64.e_shnum)
	{
		printf("No section in file\n");
		return (1);
	}
	if (!is_64(elf_headers->e_64) && !elf_headers->e_32.e_shnum)
	{
		printf("No section in file\n");
		return (1);
	}

	if (is_64(elf_headers->e_64))
		printf("There are %d section headers, starting at offset 0x%lx:\n",
			   elf_headers->e_64.e_shnum, elf_headers->e_64.e_shoff);
	else
		printf("There are %d section headers, starting at offset 0x%lx:\n",
			   elf_headers->e_32.e_shnum,
			   (unsigned long)elf_headers->e_32.e_shoff);
	handle_section_header(elf_headers, fd);
	printf("\nSection Headers:\n");
	if (is_64(elf_headers->e_64))
	{
		if (!is_little_endian(elf_headers->e_64))
			for (i = 0; i < elf_headers->e_64.e_shnum; i++)
				convert_little_to_big_end_64_section(elf_headers, i);
		print_64_section(elf_headers, fd);
	}
	else
	{
		if (!is_little_endian(elf_headers->e_64))
			for (i = 0; i < elf_headers->e_32.e_shnum; i++)
				convert_little_to_big_end_32_section(elf_headers, i);
		print_32_section(elf_headers, fd);
	}
	print_footer_section(elf_headers);
	return (0);
}

/**
* print_64_section - Print elf section header 64
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_64_section(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0;
	char *str_table = NULL;

	str_table = get_string_table(elf_headers, fd);
	printf("  [Nr] Name              Type            Address");
	printf("          Off    Size   ES Flg Lk Inf Al\n");
	for (i = 0; i < elf_headers->e_64.e_shnum; i++)
	{
		printf("  [%2u] %-17s %-15.15s %16.16lx %6.6lx",
			   i,
			   &str_table[elf_headers->es_64[i].sh_name],
			   get_elf_section_type_64(elf_headers, i),
			   elf_headers->es_64[i].sh_addr,
			   elf_headers->es_64[i].sh_offset);
		printf(" %6.6lx %2.2lx %3s %2u %3u %2lu\n",
			   elf_headers->es_64[i].sh_size,
			   elf_headers->es_64[i].sh_entsize,
			   get_elf_section_flag(elf_headers, i),
			   elf_headers->es_64[i].sh_link,
			   elf_headers->es_64[i].sh_info,
			   elf_headers->es_64[i].sh_addralign);
	}
	free(str_table);
	return (0);
}

/**
* print_32_section - Print elf section header 32
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_32_section(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0;
	char *str_table = NULL;

	str_table = get_string_table(elf_headers, fd);
	printf("  [Nr] Name              Type            Addr     ");
	printf("Off    Size   ES Flg Lk Inf Al\n");
	for (i = 0; i < elf_headers->e_32.e_shnum; i++)
	{
		printf("  [%2u] %-17s %-15.15s %8.8lx %6.6lx",
			   i,
			   &str_table[elf_headers->es_32[i].sh_name],
			   get_elf_section_type_32(elf_headers, i),
			   (unsigned long)elf_headers->es_32[i].sh_addr,
			   (unsigned long)elf_headers->es_32[i].sh_offset);
		printf(" %6.6lx %2.2lx %3s %2u %3u %2lu\n",
			   (unsigned long)elf_headers->es_32[i].sh_size,
			   (unsigned long)elf_headers->es_32[i].sh_entsize,
			   get_elf_section_flag(elf_headers, i),
			   elf_headers->es_32[i].sh_link,
			   elf_headers->es_32[i].sh_info,
			   (unsigned long)elf_headers->es_32[i].sh_addralign);
	}
	free(str_table);
	return (0);
}

/**
* print_footer_section - Print footer header section
* @elf_headers: Elf headers
* Return: 0 on success, 1 otherwise
*/
int print_footer_section(elf_struct_headers *elf_headers)
{
	char *str[] = {"Key to Flags:\n",
				   "  W (write), A (alloc), X (execute),",
				   " M (merge), S (strings)",
				   "  I (info), L (link order), G (group),",
				   " T (TLS), E (exclude), x (unknown)\n",
				   "  O (extra OS processing required) o (OS specific),",
				   " p (processor specific)\n"};
	int i = 0;

	for (i = 0; i < 7; i++)
	{
		if (i == 2)
		{
			if (is_64(elf_headers->e_64))
				printf("%s%s\n", str[i], ", l (large)");
			else
				printf("%s\n", str[i]);
		}
		else
			printf("%s", str[i]);
	}

	return (0);
}

/**
* get_elf_section_flag - Print elf section header flag
* @elf_headers: Elf headers
* @i: index
* Return: 0 on success, 1 otherwise
*/
char *get_elf_section_flag(elf_struct_headers *elf_headers, int i)
{
	static char str[6];
	char *str_cpy = str;

	if (is_64(elf_headers->e_64))
	{
		if (elf_headers->es_64[i].sh_flags & SHF_WRITE)
			*str_cpy++ = 'W';
		if (elf_headers->es_64[i].sh_flags & SHF_ALLOC)
			*str_cpy++ = 'A';
		if (elf_headers->es_64[i].sh_flags & SHF_EXECINSTR)
			*str_cpy++ = 'X';
		if (elf_headers->es_64[i].sh_flags & SHF_MERGE)
			*str_cpy++ = 'M';
		if (elf_headers->es_64[i].sh_flags & SHF_STRINGS)
			*str_cpy++ = 'S';
		if (elf_headers->es_64[i].sh_flags & SHF_INFO_LINK)
			*str_cpy++ = 'I';
		if (elf_headers->es_64[i].sh_flags & SHF_EXCLUDE)
			*str_cpy++ = 'E';
	}
	else
	{
		if (elf_headers->es_32[i].sh_flags & SHF_WRITE)
			*str_cpy++ = 'W';
		if (elf_headers->es_32[i].sh_flags & SHF_ALLOC)
			*str_cpy++ = 'A';
		if (elf_headers->es_32[i].sh_flags & SHF_EXECINSTR)
			*str_cpy++ = 'X';
		if (elf_headers->es_32[i].sh_flags & SHF_MERGE)
			*str_cpy++ = 'M';
		if (elf_headers->es_32[i].sh_flags & SHF_STRINGS)
			*str_cpy++ = 'S';
		if (elf_headers->es_32[i].sh_flags & SHF_INFO_LINK)
			*str_cpy++ = 'I';
		if (elf_headers->es_32[i].sh_flags & SHF_EXCLUDE)
			*str_cpy++ = 'E';
	}
	*str_cpy = 0;
	return (str);
}
