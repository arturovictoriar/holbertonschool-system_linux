#include "header_elf.h"

/**
* get_elf_section_type_64 - Print elf section header type 64
* @elf_headers: Elf headers
* @i: index
* Return: 0 on success, 1 otherwise
*/
char *get_elf_section_type_64(elf_struct_headers *elf_headers, int i)
{
	switch (elf_headers->es_64[i].sh_type)
	{
	case SHT_NULL:
		return ("NULL");
	case SHT_PROGBITS:
		return ("PROGBITS");
	case SHT_SYMTAB:
		return ("SYMTAB");
	case SHT_STRTAB:
		return ("STRTAB");
	case SHT_RELA:
		return ("RELA");
	case SHT_HASH:
		return ("HASH");
	case SHT_DYNAMIC:
		return ("DYNAMIC");
	case SHT_NOTE:
		return ("NOTE");
	case SHT_NOBITS:
		return ("NOBITS");
	case SHT_REL:
		return ("REL");
	case SHT_SHLIB:
		return ("SHLIB");
	case SHT_DYNSYM:
		return ("DYNSYM");
	case SHT_INIT_ARRAY:
		return ("INIT_ARRAY");
	case SHT_FINI_ARRAY:
		return ("FINI_ARRAY");
	case SHT_GROUP:
		return ("GROUP");
	case SHT_SYMTAB_SHNDX:
		return ("SYMTAB SECTION INDICIES");
	default:
		return (get_elf_section_type_64_1(elf_headers, i));
	}
}

/**
* get_elf_section_type_64_1 - Print elf section header type 64
* @elf_headers: Elf headers
* @i: index
* Return: 0 on success, 1 otherwise
*/
char *get_elf_section_type_64_1(elf_struct_headers *elf_headers, int i)
{
	static char str[25];

	switch (elf_headers->es_64[i].sh_type)
	{
	case SHT_PREINIT_ARRAY:
		return ("PREINIT_ARRAY");
	case SHT_GNU_HASH:
		return ("GNU_HASH");
	case SHT_GNU_verdef:
		return ("VERDEF");
	case SHT_GNU_verneed:
		return ("VERNEED");
	case SHT_GNU_versym:
		return ("VERSYM");
	case 0x6ffffff0:
		return ("VERSYM");
	case 0x6ffffffc:
		return ("VERDEF");
	case 0x7ffffffd:
		return ("AUXILIARY");
	case 0x7fffffff:
		return ("FILTER");
	case 0x6ffffff1:
		return ("LOOS+ffffff1");
	case 0x6ffffff3:
		return ("LOOS+ffffff3");
	case SHT_GNU_LIBLIST:
		return ("GNU_LIBLIST");
	default:
		sprintf(str, "%08x: <unknown>",
				elf_headers->es_64[i].sh_type);
		break;
	}
	return (str);
}

/**
* get_elf_section_type_32 - Print elf section header type 32
* @elf_headers: Elf headers
* @i: index
* Return: 0 on success, 1 otherwise
*/
char *get_elf_section_type_32(elf_struct_headers *elf_headers, int i)
{
	switch (elf_headers->es_32[i].sh_type)
	{
	case SHT_NULL:
		return ("NULL");
	case SHT_PROGBITS:
		return ("PROGBITS");
	case SHT_SYMTAB:
		return ("SYMTAB");
	case SHT_STRTAB:
		return ("STRTAB");
	case SHT_RELA:
		return ("RELA");
	case SHT_HASH:
		return ("HASH");
	case SHT_DYNAMIC:
		return ("DYNAMIC");
	case SHT_NOTE:
		return ("NOTE");
	case SHT_NOBITS:
		return ("NOBITS");
	case SHT_REL:
		return ("REL");
	case SHT_SHLIB:
		return ("SHLIB");
	case SHT_DYNSYM:
		return ("DYNSYM");
	case SHT_INIT_ARRAY:
		return ("INIT_ARRAY");
	case SHT_FINI_ARRAY:
		return ("FINI_ARRAY");
	case SHT_GROUP:
		return ("GROUP");
	case SHT_SYMTAB_SHNDX:
		return ("SYMTAB SECTION INDICIES");
	default:
		return (get_elf_section_type_32_1(elf_headers, i));
	}
}

/**
* get_elf_section_type_32_1 - Print elf section header type 32
* @elf_headers: Elf headers
* @i: index
* Return: 0 on success, 1 otherwise
*/
char *get_elf_section_type_32_1(elf_struct_headers *elf_headers, int i)
{
	static char str[25];

	switch (elf_headers->es_32[i].sh_type)
	{
	case SHT_PREINIT_ARRAY:
		return ("PREINIT_ARRAY");
	case SHT_GNU_HASH:
		return ("GNU_HASH");
	case SHT_GNU_verdef:
		return ("VERDEF");
	case SHT_GNU_verneed:
		return ("VERNEED");
	case SHT_GNU_versym:
		return ("VERSYM");
	case 0x6ffffff0:
		return ("VERSYM");
	case 0x6ffffffc:
		return ("VERDEF");
	case 0x7ffffffd:
		return ("AUXILIARY");
	case 0x7fffffff:
		return ("FILTER");
	case 0x6ffffff1:
		return ("LOOS+ffffff1");
	case 0x6ffffff3:
		return ("LOOS+ffffff3");
	case SHT_GNU_LIBLIST:
		return ("GNU_LIBLIST");
	default:
		sprintf(str, "%08x: <unknown>",
				elf_headers->es_32[i].sh_type);
		break;
	}
	return (str);
}
