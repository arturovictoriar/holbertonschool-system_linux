#include "header_elf.h"

/**
* convert_little_to_big_end_64_symbols - Convert big to little if elf is b_end
* @elf_h: Elf headers
* @i: index
* Return: 0 on success
*/
int convert_little_to_big_end_64_symbols(elf_struct_headers *elf_h,
										 unsigned int i)
{
	elf_h->esy_64[i].st_name = little_big_uint32_t(elf_h->esy_64[i].st_name);
	elf_h->esy_64[i].st_shndx = little_big_uint16_t(elf_h->esy_64[i].st_shndx);
	elf_h->esy_64[i].st_value = little_big_Elf64_Off(elf_h->esy_64[i].st_value);
	elf_h->esy_64[i].st_size = little_big_uint64_t(elf_h->esy_64[i].st_size);

	return (0);
}

/**
* convert_little_to_big_end_32_symbols - Convert big to little if elf is b_end
* @elf_h: Elf headers
* @i: index
* Return: 0 on success
*/
int convert_little_to_big_end_32_symbols(elf_struct_headers *elf_h,
										 unsigned int i)
{
	elf_h->esy_32[i].st_name = little_big_uint32_t(elf_h->esy_32[i].st_name);
	elf_h->esy_32[i].st_shndx = little_big_uint16_t(elf_h->esy_32[i].st_shndx);
	elf_h->esy_32[i].st_value = little_big_Elf32_Off(elf_h->esy_32[i].st_value);
	elf_h->esy_32[i].st_size = little_big_uint32_t(elf_h->esy_32[i].st_size);

	return (0);
}
