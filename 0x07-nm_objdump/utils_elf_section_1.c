#include "header_elf.h"

/**
* handle_section_header - Save the list of sections
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int handle_section_header(elf_struct_headers *elf_headers, int fd)
{
	uint16_t shnum_64 = elf_headers->e_64.e_shnum;
	uint16_t shnum_32 = elf_headers->e_32.e_shnum;
	uint16_t shentsize_64 = elf_headers->e_64.e_shentsize;
	uint16_t shentsize_32 = elf_headers->e_32.e_shentsize;
	int read_size = 0;

	if (is_64(elf_headers->e_64))
	{
		elf_headers->es_64 = calloc(shnum_64, shentsize_64);
		if (!elf_headers->es_64)
			exit(1);
		lseek(fd, elf_headers->e_64.e_shoff, SEEK_SET);
		read_size = read(fd, elf_headers->es_64, shnum_64 * shentsize_64);
		if (read_size < shnum_64 * shentsize_64)
			exit(1);
	}
	else
	{
		elf_headers->es_32 = calloc(shnum_32, shentsize_32);
		if (!elf_headers->es_32)
			exit(1);
		lseek(fd, elf_headers->e_32.e_shoff, SEEK_SET);
		read_size = read(fd, elf_headers->es_32, shnum_32 * shentsize_32);
		if (read_size < shnum_32 * shentsize_32)
			exit(1);
	}

	return (0);
}

/**
* handle_symbol_section - Save the list of symbols
* @elf_headers: Elf headers
* @fd: file descriptor
* @i: index
* Return: 0 on success, 1 otherwise
*/
int handle_symbol_section(elf_struct_headers *elf_headers, int fd, int i)
{
	uint64_t shsize_64 = 0, shentsize_64 = 0;
	uint32_t shsize_32 = 0, shentsize_32 = 0;
	unsigned int read_size = 0, j = 0;

	if (is_64(elf_headers->e_64))
	{
		shsize_64 = elf_headers->es_64[i].sh_size;
		shentsize_64 = elf_headers->es_64[i].sh_entsize;
		elf_headers->esy_64 = calloc((int)(shsize_64 / shentsize_64), shentsize_64);
		if (!elf_headers->esy_64)
			exit(1);
		lseek(fd, elf_headers->es_64[i].sh_offset, SEEK_SET);
		read_size = read(fd, elf_headers->esy_64, shsize_64);
		if (read_size < shsize_64)
			exit(1);
		if (!is_little_endian(elf_headers->e_64))
			for (j = 0; j < (unsigned int)(shsize_64 / shentsize_64); j++)
				convert_little_to_big_end_64_symbols(elf_headers, j);
	}
	else
	{
		shsize_32 = elf_headers->es_32[i].sh_size;
		shentsize_32 = elf_headers->es_32[i].sh_entsize;
		elf_headers->esy_32 = calloc((int)(shsize_32 / shentsize_32), shentsize_32);
		if (!elf_headers->esy_32)
			exit(1);
		lseek(fd, elf_headers->es_32[i].sh_offset, SEEK_SET);
		read_size = read(fd, elf_headers->esy_32, shsize_32);
		if (read_size < shsize_32)
			exit(1);
		if (!is_little_endian(elf_headers->e_64))
			for (j = 0; j < (unsigned int)(shsize_32 / shentsize_32); j++)
				convert_little_to_big_end_32_symbols(elf_headers, j);
	}

	return (0);
}

/**
* clean_section_64_32 - Clean the list of sections
* @elf_headers: Elf headers
* Return: 0 on success, 1 otherwise
*/
int clean_section_64_32(elf_struct_headers *elf_headers)
{
	if (is_64(elf_headers->e_64))
	{
		free(elf_headers->es_64);
		elf_headers->es_64 = NULL;
	}
	else
	{
		free(elf_headers->es_32);
		elf_headers->es_32 = NULL;
	}

	return (0);
}

/**
 * get_string_table - reads the string table
 * @elf_headers: the internal header
 * @fd: file descriptor to read
 * Return: start table
 */
char *get_string_table(elf_struct_headers *elf_headers, int fd)
{
	char *str;

	if (is_64(elf_headers->e_64))
	{
		str = calloc(1,
					 elf_headers->es_64[elf_headers->e_64.e_shstrndx].sh_size);
		if (!str)
			exit(1);

		lseek(fd, elf_headers->es_64[elf_headers->e_64.e_shstrndx].sh_offset,
			  SEEK_SET);
		read(fd, str,
			 elf_headers->es_64[elf_headers->e_64.e_shstrndx].sh_size);
	}
	else
	{
		str = calloc(1,
					 elf_headers->es_32[elf_headers->e_32.e_shstrndx].sh_size);
		if (!str)
			exit(1);

		lseek(fd, elf_headers->es_32[elf_headers->e_32.e_shstrndx].sh_offset,
			  SEEK_SET);
		read(fd, str,
			 elf_headers->es_32[elf_headers->e_32.e_shstrndx].sh_size);
	}
	return (str);
}

/**
 * get_sym_string_table - reads the symbol string table
 * @elf_headers: the internal header
 * @fd: file descriptor to read
 * @i: index
 * Return: start table
 */
char *get_sym_string_table(elf_struct_headers *elf_headers, int fd, int i)
{
	char *str;

	if (is_64(elf_headers->e_64))
	{
		str = calloc(1,
					 elf_headers->es_64[i].sh_size);
		if (!str)
			exit(1);

		lseek(fd, elf_headers->es_64[i].sh_offset,
			  SEEK_SET);
		read(fd, str,
			 elf_headers->es_64[i].sh_size);
	}
	else
	{
		str = calloc(1,
					 elf_headers->es_32[i].sh_size);
		if (!str)
			exit(1);

		lseek(fd, elf_headers->es_32[i].sh_offset,
			  SEEK_SET);
		read(fd, str,
			 elf_headers->es_32[i].sh_size);
	}
	return (str);
}
