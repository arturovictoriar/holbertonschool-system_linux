#include "header_elf.h"

/**
* convert_little_to_big_end_64_section - Convert big to little if elf is b_end
* @elf_h: Elf headers
* @i: index
* Return: 0 on success
*/
int convert_little_to_big_end_64_section(elf_struct_headers *elf_h,
										 unsigned int i)
{
	elf_h->es_64[i].sh_name = little_big_uint32_t(elf_h->es_64[i].sh_name);
	elf_h->es_64[i].sh_type = little_big_uint32_t(elf_h->es_64[i].sh_type);
	elf_h->es_64[i].sh_flags = little_big_uint64_t(elf_h->es_64[i].sh_flags);
	elf_h->es_64[i].sh_addr = little_big_Elf64_Addr(elf_h->es_64[i].sh_addr);
	elf_h->es_64[i].sh_offset = little_big_Elf64_Off(elf_h->es_64[i].sh_offset);
	elf_h->es_64[i].sh_size = little_big_uint64_t(elf_h->es_64[i].sh_size);
	elf_h->es_64[i].sh_link = little_big_uint32_t(elf_h->es_64[i].sh_link);
	elf_h->es_64[i].sh_info = little_big_uint32_t(elf_h->es_64[i].sh_info);
	elf_h->es_64[i].sh_addralign = little_big_uint64_t(
		elf_h->es_64[i].sh_addralign);
	elf_h->es_64[i].sh_entsize = little_big_uint64_t(elf_h->es_64[i].sh_entsize);

	return (0);
}

/**
* convert_little_to_big_end_32_section - Convert big to little if elf is b_end
* @elf_h: Elf headers
* @i: index
* Return: 0 on success
*/
int convert_little_to_big_end_32_section(elf_struct_headers *elf_h,
										 unsigned int i)
{
	elf_h->es_32[i].sh_name = little_big_uint32_t(elf_h->es_32[i].sh_name);
	elf_h->es_32[i].sh_type = little_big_uint32_t(elf_h->es_32[i].sh_type);
	elf_h->es_32[i].sh_flags = little_big_uint32_t(elf_h->es_32[i].sh_flags);
	elf_h->es_32[i].sh_addr = little_big_Elf32_Addr(elf_h->es_32[i].sh_addr);
	elf_h->es_32[i].sh_offset = little_big_Elf32_Off(elf_h->es_32[i].sh_offset);
	elf_h->es_32[i].sh_size = little_big_uint32_t(elf_h->es_32[i].sh_size);
	elf_h->es_32[i].sh_link = little_big_uint32_t(elf_h->es_32[i].sh_link);
	elf_h->es_32[i].sh_info = little_big_uint32_t(elf_h->es_32[i].sh_info);
	elf_h->es_32[i].sh_addralign = little_big_uint32_t(
		elf_h->es_32[i].sh_addralign);
	elf_h->es_32[i].sh_entsize = little_big_uint32_t(elf_h->es_32[i].sh_entsize);

	return (0);
}

/**
* convert_little_to_big_end_64_program - Convert big to little if elf is b_end
* @elf_h: Elf headers
* @i: index
* Return: 0 on success
*/
int convert_little_to_big_end_64_program(elf_struct_headers *elf_h,
										 unsigned int i)
{
	elf_h->ep_64[i].p_type = little_big_uint32_t(elf_h->ep_64[i].p_type);
	elf_h->ep_64[i].p_offset = little_big_Elf64_Off(elf_h->ep_64[i].p_offset);
	elf_h->ep_64[i].p_vaddr = little_big_Elf64_Addr(elf_h->ep_64[i].p_vaddr);
	elf_h->ep_64[i].p_paddr = little_big_Elf64_Addr(elf_h->ep_64[i].p_paddr);
	elf_h->ep_64[i].p_filesz = little_big_Elf64_Off(elf_h->ep_64[i].p_filesz);
	elf_h->ep_64[i].p_memsz = little_big_uint64_t(elf_h->ep_64[i].p_memsz);
	elf_h->ep_64[i].p_flags = little_big_uint32_t(elf_h->ep_64[i].p_flags);
	elf_h->ep_64[i].p_align = little_big_uint64_t(elf_h->ep_64[i].p_align);

	return (0);
}

/**
* convert_little_to_big_end_32_program - Convert big to little if elf is b_end
* @elf_h: Elf headers
* @i: index
* Return: 0 on success
*/
int convert_little_to_big_end_32_program(elf_struct_headers *elf_h,
										 unsigned int i)
{
	elf_h->ep_32[i].p_type = little_big_uint32_t(elf_h->ep_32[i].p_type);
	elf_h->ep_32[i].p_offset = little_big_Elf32_Off(elf_h->ep_32[i].p_offset);
	elf_h->ep_32[i].p_vaddr = little_big_Elf32_Addr(elf_h->ep_32[i].p_vaddr);
	elf_h->ep_32[i].p_paddr = little_big_Elf32_Addr(elf_h->ep_32[i].p_paddr);
	elf_h->ep_32[i].p_filesz = little_big_Elf32_Off(elf_h->ep_32[i].p_filesz);
	elf_h->ep_32[i].p_memsz = little_big_uint32_t(elf_h->ep_32[i].p_memsz);
	elf_h->ep_32[i].p_flags = little_big_uint32_t(elf_h->ep_32[i].p_flags);
	elf_h->ep_32[i].p_align = little_big_uint32_t(elf_h->ep_32[i].p_align);

	return (0);
}

/**
* little_big_uint64_t - Convert big to little endian 64 bit
* @x: 64 variable
* Return: x converted
*/
uint64_t little_big_uint64_t(uint64_t x)
{
	return (((x & 0xff) << 56) |
			((x & 0xff00) << 40) |
			((x & 0xff0000) << 24) |
			((x & 0xff000000) << 8) |
			((x & 0xff00000000) >> 8) |
			((x & 0xff0000000000) >> 24) |
			((x & 0xff000000000000) >> 40) |
			((x & 0xff00000000000000) >> 56));
}
