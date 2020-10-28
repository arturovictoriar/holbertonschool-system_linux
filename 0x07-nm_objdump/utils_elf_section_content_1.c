#include "header_elf.h"

/**
 * get_section_content - reads the content of a section
 * @elf_headers: the internal header
 * @fd: file descriptor to read
 * @i: index
 * Return: start table
 */
unsigned char *get_section_content(elf_struct_headers *elf_headers, int fd,
								   int i)
{
	unsigned char *str;

	if (is_64(elf_headers->e_64))
	{
		str = calloc(1, elf_headers->es_64[i].sh_size);
		if (!str)
			exit(1);

		lseek(fd, elf_headers->es_64[i].sh_offset, SEEK_SET);
		read(fd, str, elf_headers->es_64[i].sh_size);
	}
	else
	{
		str = calloc(1, elf_headers->es_32[i].sh_size);
		if (!str)
			exit(1);

		lseek(fd, elf_headers->es_32[i].sh_offset, SEEK_SET);
		read(fd, str, elf_headers->es_32[i].sh_size);
	}

	return (str);
}

/**
 * get_ftype - get the type file
 * @elf_headers: the internal header
 * Return: start table
 */
char *get_ftype(elf_struct_headers *elf_headers)
{
	static char type[20] = {0};

	sprintf(type, "elf%d-%s",
			is_64(elf_headers->e_64) ? 64 : 32,
			!is_little_endian(elf_headers->e_64)
				? "big"
				: is_64(elf_headers->e_64)
					  ? "x86-64"
					  : "i386");
	return (type);
}

/**
* max_len_64 - max len in add 64
* @elf_headers: Elf headers
* @i: index section header
* Return: max len in addr
*/
int max_len_64(elf_struct_headers *elf_headers, unsigned int i)
{
	unsigned int max_add = 0;
	char addr[20] = {0};

	max_add = sprintf(addr, "%lx",
					  elf_headers->es_64[i].sh_addr + elf_headers->es_64[i].sh_size);
	if (max_add < 4)
		return (4);
	return (max_add);
}

/**
* max_len_32 - max len in add 32
* @elf_headers: Elf headers
* @i: index section header
* Return: max len in addr
*/
int max_len_32(elf_struct_headers *elf_headers, unsigned int i)
{
	unsigned int max_add = 0;
	char addr[20] = {0};

	max_add = sprintf(addr, "%lx",
					  (unsigned long)(elf_headers->es_32[i].sh_addr +
									  elf_headers->es_32[i].sh_size));
	if (max_add < 4)
		return (4);
	return (max_add);
}
