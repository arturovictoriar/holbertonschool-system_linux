#include "header_elf.h"

/**
* handle_program_header - Save the list of segments
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int handle_program_header(elf_struct_headers *elf_headers, int fd)
{
	uint16_t phnum_64 = elf_headers->e_64.e_phnum;
	uint16_t phnum_32 = elf_headers->e_32.e_phnum;
	uint16_t phentsize_64 = elf_headers->e_64.e_phentsize;
	uint16_t phentsize_32 = elf_headers->e_32.e_phentsize;
	int read_size = 0;

	if (is_64(elf_headers->e_64))
	{
		elf_headers->ep_64 = calloc(phnum_64, phentsize_64);
		if (!elf_headers->ep_64)
			exit(1);
		lseek(fd, elf_headers->e_64.e_phoff, SEEK_SET);
		read_size = read(fd, elf_headers->ep_64, phnum_64 * phentsize_64);
		if (read_size < phnum_64 * phentsize_64)
			exit(1);
	}
	else
	{
		elf_headers->ep_32 = calloc(phnum_32, phentsize_32);
		if (!elf_headers->ep_32)
			exit(1);
		lseek(fd, elf_headers->e_32.e_phoff, SEEK_SET);
		read_size = read(fd, elf_headers->ep_32, phnum_32 * phentsize_32);
		if (read_size < phnum_32 * phentsize_32)
			exit(1);
	}

	return (0);
}

/**
* clean_program_64_32 - Clean the list of segments
* @elf_headers: Elf headers
* Return: 0 on success, 1 otherwise
*/
int clean_program_64_32(elf_struct_headers *elf_headers)
{
	if (is_64(elf_headers->e_64))
		free(elf_headers->ep_64);
	else
		free(elf_headers->ep_32);

	return (0);
}

/**
* get_section_program_64_32 - check if a section belong a segment
* @elf_headers: Elf headers
* @i: index program
* @j: index section
* Return: 1 on success, 0 otherwise
*/
int get_section_program_64_32(elf_struct_headers *elf_headers, unsigned int i,
							  unsigned int j)
{
	if (is_64(elf_headers->e_64))
	{
		if (elf_headers->es_64[j].sh_size &&
			(elf_headers->es_64[j].sh_addr >=
			 elf_headers->ep_64[i].p_vaddr) &&
			(elf_headers->es_64[j].sh_addr <
			 (elf_headers->ep_64[i].p_vaddr +
			  elf_headers->ep_64[i].p_memsz)))
			return (1);
	}
	else
	{
		if (elf_headers->es_32[j].sh_size &&
			(elf_headers->es_32[j].sh_addr >=
			 elf_headers->ep_32[i].p_vaddr) &&
			(elf_headers->es_32[j].sh_addr <
			 (elf_headers->ep_32[i].p_vaddr +
			  elf_headers->ep_32[i].p_memsz)))
			return (1);
	}

	return (0);
}
