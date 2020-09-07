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
		if (elf_headers->ep_64)
			exit(1);
		lseek(fd, elf_headers->e_64.e_shoff, SEEK_SET);
		read_size = read(fd, elf_headers->es_64, shnum_64 * shentsize_64);
		if (read_size < shnum_64 * shentsize_64)
			exit(1);
	}
	else
	{
		elf_headers->es_32 = calloc(shnum_32, shentsize_32);
		if (elf_headers->ep_32)
			exit(1);
		lseek(fd, elf_headers->e_32.e_shoff, SEEK_SET);
		read_size = read(fd, elf_headers->es_32, shnum_32 * shentsize_32);
		if (read_size < shnum_32 * shentsize_32)
			exit(1);
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
		free(elf_headers->es_64);
	else
		free(elf_headers->es_32);

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
