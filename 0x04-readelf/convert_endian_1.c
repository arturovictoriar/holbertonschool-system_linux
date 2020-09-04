#include "header_elf.h"

/**
* convert_little_to_big_end_64 - Convert big to little if elf is b_endian
* @elf_h: Elf headers
* Return: 0 on success
*/
int convert_little_to_big_end_64(elf_struct_headers *elf_h)
{
	elf_h->e_64.e_type = little_big_uint16_t(elf_h->e_64.e_type);
	elf_h->e_64.e_machine = little_big_uint16_t(elf_h->e_64.e_machine);
	elf_h->e_64.e_version = little_big_uint32_t(elf_h->e_64.e_version);
	elf_h->e_64.e_entry = little_big_Elf64_Addr(elf_h->e_64.e_entry);
	elf_h->e_64.e_phoff = little_big_Elf64_Off(elf_h->e_64.e_phoff);
	elf_h->e_64.e_shoff = little_big_Elf64_Off(elf_h->e_64.e_shoff);
	elf_h->e_64.e_flags = little_big_uint32_t(elf_h->e_64.e_flags);
	elf_h->e_64.e_ehsize = little_big_uint16_t(elf_h->e_64.e_ehsize);
	elf_h->e_64.e_phentsize = little_big_uint16_t(elf_h->e_64.e_phentsize);
	elf_h->e_64.e_phnum = little_big_uint16_t(elf_h->e_64.e_phnum);
	elf_h->e_64.e_shentsize = little_big_uint16_t(elf_h->e_64.e_shentsize);
	elf_h->e_64.e_shnum = little_big_uint16_t(elf_h->e_64.e_shnum);
	elf_h->e_64.e_shstrndx = little_big_uint16_t(elf_h->e_64.e_shstrndx);
	if (!is_64(elf_h->e_64))
		convert_little_to_big_end_32(elf_h);

	return (0);
}

/**
* convert_little_to_big_end_32 - Convert big to little if elf is b_endian
* @elf_h: Elf headers
* Return: 0 on success
*/
int convert_little_to_big_end_32(elf_struct_headers *elf_h)
{
	elf_h->e_32.e_type = little_big_uint16_t(elf_h->e_32.e_type);
	elf_h->e_32.e_machine = little_big_uint16_t(elf_h->e_32.e_machine);
	elf_h->e_32.e_version = little_big_uint32_t(elf_h->e_32.e_version);
	elf_h->e_32.e_entry = little_big_Elf32_Addr(elf_h->e_32.e_entry);
	elf_h->e_32.e_phoff = little_big_Elf32_Off(elf_h->e_32.e_phoff);
	elf_h->e_32.e_shoff = little_big_Elf32_Off(elf_h->e_32.e_shoff);
	elf_h->e_32.e_flags = little_big_uint32_t(elf_h->e_32.e_flags);
	elf_h->e_32.e_ehsize = little_big_uint16_t(elf_h->e_32.e_ehsize);
	elf_h->e_32.e_phentsize = little_big_uint16_t(elf_h->e_32.e_phentsize);
	elf_h->e_32.e_phnum = little_big_uint16_t(elf_h->e_32.e_phnum);
	elf_h->e_32.e_shentsize = little_big_uint16_t(elf_h->e_32.e_shentsize);
	elf_h->e_32.e_shnum = little_big_uint16_t(elf_h->e_32.e_shnum);
	elf_h->e_32.e_shstrndx = little_big_uint16_t(elf_h->e_32.e_shstrndx);

	return (0);
}

/**
* little_big_uint16_t - Convert big to little endian 16 bit
* @x: 16 variable
* Return: x converted
*/
uint16_t little_big_uint16_t(uint16_t x)
{
	return (((x & 0xff) << 8) |
			((x & 0xff00) >> 8));
}
