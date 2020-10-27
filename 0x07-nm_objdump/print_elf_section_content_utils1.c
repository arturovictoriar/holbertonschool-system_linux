#include "header_elf.h"

/**
* print_elf_section_content - Print sections content
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_elf_section_content(elf_struct_headers *elf_headers, int fd)
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
		print_64_section_content(elf_headers, fd);
	}
	else
	{
		if (!is_little_endian(elf_headers->e_64))
			for (i = 0; i < elf_headers->e_32.e_shnum; i++)
				convert_little_to_big_end_32_section(elf_headers, i);
		print_32_section_content(elf_headers, fd);
	}
	return (0);
}

/**
* print_64_section_content - Print elf sections content 64
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_64_section_content(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0, j = 0;
	char *str_table = get_string_table(elf_headers, fd);
	unsigned char *content_s = NULL;

	printf("\n");
	for (i = 0; i < elf_headers->e_64.e_shnum; i++)
	{
		if ((strcmp(&str_table[elf_headers->es_64[i].sh_name], ".dynstr") &&
			 ((!strncmp(&str_table[elf_headers->es_64[i].sh_name], ".rel", 4) &&
			   !elf_headers->es_64[i].sh_addr) ||
			  elf_headers->es_64[i].sh_type == SHT_SYMTAB ||
			  elf_headers->es_64[i].sh_type == SHT_NOBITS ||
			  elf_headers->es_64[i].sh_type == SHT_STRTAB ||
			  !elf_headers->es_64[i].sh_size)))
			continue;
		content_s = get_section_content(elf_headers, fd, i);
		printf("Contents of section %s:\n",
			   &str_table[elf_headers->es_64[i].sh_name]);
		for (j = 1; j <= elf_headers->es_64[i].sh_size; j++)
			section_content_64(elf_headers, i, j, content_s);
		free(content_s);
		content_s = NULL;
	}
	free(str_table);
	return (0);
}

/**
* section_content_64 - Print elf section content 64
* @elf_headers: Elf headers
* @i: index section header
* @j: index section content
* @content_s: content of the section
* Return: 0 on success, 1 otherwise
*/
int section_content_64(elf_struct_headers *elf_headers, unsigned int i,
					   unsigned int j, unsigned char *content_s)
{
	unsigned int k = 0, l = 0;

	if (j == 1)
		printf(" %.4lx ", elf_headers->es_64[i].sh_addr);
	printf("%.2x", content_s[j - 1]);
	if (j % 4 == 0)
		printf(" ");
	if (j % 16 == 0 || j == elf_headers->es_64[i].sh_size)
	{
		if (j % 16 != 0)
			for (l = 0;
				 l < ((16 - (j % 16)) * 2) +
						 ((j % 16 < 4)
							  ? 4
							  : (j % 16 < 8) ? 3 : (j % 16 < 12) ? 2 : 1);
				 l++)
				printf(" ");
		printf(" ");
		for (k = ((j == elf_headers->es_64[i].sh_size) &&
				  ((j % 16) != 0))
					 ? j - (j % 16)
					 : j - 16;
			 k < j;
			 k++)
			printf("%c",
				   (content_s[k] >= 32 && content_s[k] <= 126) ? content_s[k] : '.');
		if ((j == elf_headers->es_64[i].sh_size) && ((j % 16) != 0))
			for (k = j % 16; k < 16; k++)
				printf(" ");
		printf("\n");
	}
	if (j % 16 == 0 && j != elf_headers->es_64[i].sh_size)
		printf(" %.4lx ", elf_headers->es_64[i].sh_addr + j);
	return (0);
}

/**
* print_32_section_content - Print elf section content 32
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_32_section_content(elf_struct_headers *elf_headers, int fd)
{
	unsigned int i = 0, j = 0;
	char *str_table = get_string_table(elf_headers, fd);
	unsigned char *content_s = NULL;

	printf("\n");
	for (i = 0; i < elf_headers->e_32.e_shnum; i++)
	{
		if ((strcmp(&str_table[elf_headers->es_32[i].sh_name], ".dynstr") &&
			 ((!strncmp(&str_table[elf_headers->es_32[i].sh_name], ".rel", 4) &&
			   !elf_headers->es_32[i].sh_addr) ||
			  elf_headers->es_32[i].sh_type == SHT_SYMTAB ||
			  elf_headers->es_32[i].sh_type == SHT_NOBITS ||
			  elf_headers->es_32[i].sh_type == SHT_STRTAB ||
			  !elf_headers->es_32[i].sh_size)))
			continue;
		content_s = get_section_content(elf_headers, fd, i);
		printf("Contents of section %s:\n",
			   &str_table[elf_headers->es_32[i].sh_name]);
		for (j = 1; j <= elf_headers->es_32[i].sh_size; j++)
			section_content_32(elf_headers, i, j, content_s);
		free(content_s);
		content_s = NULL;
	}
	free(str_table);
	return (0);
}

/**
* section_content_32 - Print elf section content 32
* @elf_headers: Elf headers
* @i: index section header
* @j: index section content
* @content_s: content of the section
* Return: 0 on success, 1 otherwise
*/
int section_content_32(elf_struct_headers *elf_headers, unsigned int i,
					   unsigned int j, unsigned char *content_s)
{
	unsigned int k = 0, l = 0;

	if (j == 1)
		printf(" %.4lx ", (unsigned long)elf_headers->es_32[i].sh_addr);
	printf("%.2x", content_s[j - 1]);
	if (j % 4 == 0)
		printf(" ");
	if (j % 16 == 0 || j == elf_headers->es_32[i].sh_size)
	{
		if (j % 16 != 0)
			for (l = 0;
				 l < ((16 - (j % 16)) * 2) +
						 ((j % 16 < 4)
							  ? 4
							  : (j % 16 < 8) ? 3 : (j % 16 < 12) ? 2 : 1);
				 l++)
				printf(" ");
		printf(" ");
		for (k = ((j == elf_headers->es_32[i].sh_size) &&
				  ((j % 16) != 0))
					 ? j - (j % 16)
					 : j - 16;
			 k < j;
			 k++)
			printf("%c",
				   (content_s[k] >= 32 && content_s[k] <= 126) ? content_s[k] : '.');
		if ((j == elf_headers->es_32[i].sh_size) && ((j % 16) != 0))
			for (k = j % 16; k < 16; k++)
				printf(" ");
		printf("\n");
	}
	if (j % 16 == 0 && j != elf_headers->es_32[i].sh_size)
		printf(" %.4lx ", (unsigned long)elf_headers->es_32[i].sh_addr + j);
	return (0);
}
