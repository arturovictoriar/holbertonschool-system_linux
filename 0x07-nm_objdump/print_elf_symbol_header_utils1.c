#include "header_elf.h"

/**
* print_elf_symbol_header - Print symbol header
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_elf_symbol_header(elf_struct_headers *elf_headers, int fd)
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

	handle_section_header(elf_headers, fd);
	if (is_64(elf_headers->e_64))
	{
		if (!is_little_endian(elf_headers->e_64))
			for (i = 0; i < elf_headers->e_64.e_shnum; i++)
				convert_little_to_big_end_64_section(elf_headers, i);
		if (print_64_symbol(elf_headers, fd))
			return (1);
	}
	else
	{
		if (!is_little_endian(elf_headers->e_64))
			for (i = 0; i < elf_headers->e_32.e_shnum; i++)
				convert_little_to_big_end_32_section(elf_headers, i);
		if (print_32_symbol(elf_headers, fd))
			return (1);
	}
	return (0);
}

/**
* print_64_symbol - Print elf symbol header 64
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_64_symbol(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0, j = 0, no_s = 0;
	char *str_table = get_string_table(elf_headers, fd);
	char *sstr_table = get_sstring_table(elf_headers, fd, str_table);

	for (i = 0; i < elf_headers->e_64.e_shnum; i++)
	{
		if (!strcmp(&str_table[elf_headers->es_64[i].sh_name], ".symtab"))
		{
			no_s = (handle_symbol_section(elf_headers, fd, i), 1);
			for (j = 1;
				 j < (unsigned int)(elf_headers->es_64[i].sh_size /
									elf_headers->es_64[i].sh_entsize);
				 j++)
			{
				if ((elf_headers->esy_64[j].st_info != STT_SECTION &&
					 elf_headers->esy_64[j].st_info != STT_FILE && j))
				{
					if (get_chr_type_symbol1_64(elf_headers, j) != 'U' &&
						get_chr_type_symbol1_64(elf_headers, j) != 'w')
						printf("%16.16lx ", (unsigned long)elf_headers->esy_64[j].st_value);
					else
						printf("%16.16s ", "");
					printf("%c %s\n",
						   get_chr_type_symbol1_64(elf_headers, j),
						   &sstr_table[elf_headers->esy_64[j].st_name]);
				}
			}
			break;
		}
	}
	free(sstr_table);
	free(str_table);
	if (!no_s)
		return (1);
	return (0);
}

/**
* print_32_symbol - Print elf symbol header 32
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_32_symbol(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0, j = 0, no_s = 0;
	char *str_table = get_string_table(elf_headers, fd);
	char *sstr_table = get_sstring_table(elf_headers, fd, str_table);

	for (i = 0; i < elf_headers->e_32.e_shnum; i++)
	{
		if (!strcmp(&str_table[elf_headers->es_32[i].sh_name], ".symtab"))
		{
			no_s = (handle_symbol_section(elf_headers, fd, i), 1);
			for (j = 1;
				 j < (unsigned int)(elf_headers->es_32[i].sh_size /
									elf_headers->es_32[i].sh_entsize);
				 j++)
			{
				if ((elf_headers->esy_32[j].st_info != STT_SECTION &&
					 elf_headers->esy_32[j].st_info != STT_FILE && j))
				{
					if (get_chr_type_symbol1_32(elf_headers, j) != 'U' &&
						get_chr_type_symbol1_32(elf_headers, j) != 'w')
						printf("%8.8lx ", (unsigned long)elf_headers->esy_32[j].st_value);
					else
						printf("%8.8s ", "");
					printf("%c %s\n",
						   get_chr_type_symbol1_32(elf_headers, j),
						   &sstr_table[elf_headers->esy_32[j].st_name]);
				}
			}
			break;
		}
	}
	free(sstr_table);
	free(str_table);
	if (!no_s)
		return (1);
	return (0);
}

char *get_sstring_table(elf_struct_headers *elf_headers, int fd,
						char *str_table)
{
	unsigned int i = 0;
	char *sstr_table = NULL;

	if (is_64(elf_headers->e_64))
	{
		for (i = 0; i < elf_headers->e_64.e_shnum; i++)
		{
			if (!strcmp(&str_table[elf_headers->es_64[i].sh_name], ".strtab"))
			{
				sstr_table = get_sym_string_table(elf_headers, fd, i);
				break;
			}
		}
	}
	else
	{
		for (i = 0; i < elf_headers->e_32.e_shnum; i++)
		{
			if (!strcmp(&str_table[elf_headers->es_32[i].sh_name], ".strtab"))
			{
				sstr_table = get_sym_string_table(elf_headers, fd, i);
				break;
			}
		}
	}

	return (sstr_table);
}
