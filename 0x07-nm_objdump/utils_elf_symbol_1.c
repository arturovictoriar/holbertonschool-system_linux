#include "header_elf.h"

/**
* get_chr_type_symbol1_32 - get the char type of the symbol 32 bits
* @elf_headers: Elf headers
* @i: index
* Return: char representing the symbol type
*/
char get_chr_type_symbol1_32(elf_struct_headers *elf_headers, int i)
{
	char c;
	uint16_t idx_s_t = elf_headers->esy_32[i].st_shndx;

	if (ELF32_ST_BIND(elf_headers->esy_32[i].st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(elf_headers->esy_32[i].st_info) == STB_WEAK &&
			 ELF32_ST_TYPE(elf_headers->esy_32[i].st_info) == STT_OBJECT)
	{
		if (idx_s_t == SHN_UNDEF)
			c = 'v';
		else
			c = 'V';
	}
	else if (ELF32_ST_BIND(elf_headers->esy_32[i].st_info) == STB_WEAK)
	{
		if (idx_s_t == SHN_UNDEF)
			c = 'w';
		else
			c = 'W';
	}
	else if (idx_s_t == SHN_UNDEF)
		c = 'U';
	else if (idx_s_t == SHN_ABS)
		c = 'A';
	else if (idx_s_t == SHN_COMMON)
		c = 'C';
	else if (elf_headers->es_32[idx_s_t].sh_type == SHT_NOBITS &&
			 elf_headers->es_32[idx_s_t].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (elf_headers->es_32[idx_s_t].sh_type == SHT_PROGBITS &&
			 elf_headers->es_32[idx_s_t].sh_flags == SHF_ALLOC)
		c = 'R';
	else
		c = get_chr_type_symbol2_32(elf_headers, i);

	if (ELF32_ST_BIND(elf_headers->esy_32[i].st_info) == STB_LOCAL &&
		c != '?')
		c += 32;
	return (c);
}

/**
* get_chr_type_symbol2_32 - get the char type of the symbol 32 bits
* @elf_headers: Elf headers
* @i: index
* Return: char representing the symbol type
*/
char get_chr_type_symbol2_32(elf_struct_headers *elf_headers, int i)
{
	char c;
	uint16_t idx_s_t = elf_headers->esy_32[i].st_shndx;

	if (elf_headers->es_32[idx_s_t].sh_type == SHT_PROGBITS &&
		elf_headers->es_32[idx_s_t].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (elf_headers->es_32[idx_s_t].sh_type == SHT_PROGBITS &&
			 elf_headers->es_32[idx_s_t].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (elf_headers->es_32[idx_s_t].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	return (c);
}

/**
* get_chr_type_symbol1_64 - get the char type of the symbol 64 bits
* @elf_headers: Elf headers
* @i: index
* Return: char representing the symbol type
*/
char get_chr_type_symbol1_64(elf_struct_headers *elf_headers, int i)
{
	char c;
	uint16_t idx_s_t = elf_headers->esy_64[i].st_shndx;

	if (ELF64_ST_BIND(elf_headers->esy_64[i].st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(elf_headers->esy_64[i].st_info) == STB_WEAK &&
			 ELF64_ST_TYPE(elf_headers->esy_64[i].st_info) == STT_OBJECT)
	{
		if (idx_s_t == SHN_UNDEF)
			c = 'v';
		else
			c = 'V';
	}
	else if (ELF64_ST_BIND(elf_headers->esy_64[i].st_info) == STB_WEAK)
	{
		if (idx_s_t == SHN_UNDEF)
			c = 'w';
		else
			c = 'W';
	}
	else if (idx_s_t == SHN_UNDEF)
		c = 'U';
	else if (idx_s_t == SHN_ABS)
		c = 'A';
	else if (idx_s_t == SHN_COMMON)
		c = 'C';
	else if (elf_headers->es_64[idx_s_t].sh_type == SHT_NOBITS &&
			 elf_headers->es_64[idx_s_t].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (elf_headers->es_64[idx_s_t].sh_type == SHT_PROGBITS &&
			 elf_headers->es_64[idx_s_t].sh_flags == SHF_ALLOC)
		c = 'R';
	else
		c = get_chr_type_symbol2_64(elf_headers, i);

	if (ELF64_ST_BIND(elf_headers->esy_64[i].st_info) == STB_LOCAL &&
		c != '?')
		c += 32;
	return (c);
}

/**
* get_chr_type_symbol2_64 - get the char type of the symbol 64 bits
* @elf_headers: Elf headers
* @i: index
* Return: char representing the symbol type
*/
char get_chr_type_symbol2_64(elf_struct_headers *elf_headers, int i)
{
	char c;
	uint16_t idx_s_t = elf_headers->esy_64[i].st_shndx;

	if (elf_headers->es_64[idx_s_t].sh_type == SHT_PROGBITS &&
		elf_headers->es_64[idx_s_t].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (elf_headers->es_64[idx_s_t].sh_type == SHT_PROGBITS &&
			 elf_headers->es_64[idx_s_t].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (elf_headers->es_64[idx_s_t].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	return (c);
}

/**
* clean_symbol_64_32 - Clean the list of sections and symbols
* @elf_headers: Elf headers
* Return: 0 on success, 1 otherwise
*/
int clean_symbol_64_32(elf_struct_headers *elf_headers)
{
	if (is_64(elf_headers->e_64))
	{
		free(elf_headers->es_64);
		elf_headers->es_64 = NULL;
		free(elf_headers->esy_64);
		elf_headers->esy_64 = NULL;
	}
	else
	{
		free(elf_headers->es_32);
		elf_headers->es_32 = NULL;
		free(elf_headers->esy_32);
		elf_headers->esy_32 = NULL;
	}

	return (0);
}
