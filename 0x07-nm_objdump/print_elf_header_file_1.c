#include "header_elf.h"

/**
 * print_file_flags - print the file's flags
 * @flags: flags to print
 * Return: 0 always
 */
int print_file_flags(unsigned long flags)
{
	int pos_1 = 1;

	if (flags & HAS_RELOC)
		pos_1 = (printf("%sHAS_RELOC", pos_1 ? "" : ", "), 0);
	if (flags & EXEC_P)
		pos_1 = (printf("%sEXEC_P", pos_1 ? "" : ", "), 0);
	if (flags & HAS_LINENO)
		pos_1 = (printf("%sHAS_LINENO", pos_1 ? "" : ", "), 0);
	if (flags & HAS_DEBUG)
		pos_1 = (printf("%sHAS_DEBUG", pos_1 ? "" : ", "), 0);
	if (flags & HAS_SYMS)
		pos_1 = (printf("%sHAS_SYMS", pos_1 ? "" : ", "), 0);
	if (flags & HAS_LOCALS)
		pos_1 = (printf("%sHAS_LOCALS", pos_1 ? "" : ", "), 0);
	if (flags & DYNAMIC)
		pos_1 = (printf("%sDYNAMIC", pos_1 ? "" : ", "), 0);
	if (flags & WP_TEXT)
		pos_1 = (printf("%sWP_TEXT", pos_1 ? "" : ", "), 0);
	if (flags & D_PAGED)
		pos_1 = (printf("%sD_PAGED", pos_1 ? "" : ", "), 0);
	if (!pos_1)
		printf("\n");
	return (0);
}

/**
 * verification_section_64 - verify is the section is in the file
 * @elf_headers: Elf headers
 * @str_table: string table
 * @sect: section to verify
 * Return: 1 on sucess, 0 otherwise
 */
int verification_section_64(elf_struct_headers *elf_headers, char *str_table,
	char *sect)
{
	unsigned int i = 0;

	for (i = 1; i < elf_headers->e_64.e_shnum; i++)
		if (!strcmp(&str_table[elf_headers->es_64[i].sh_name], sect))
			return (1);
	return (0);
}

/**
* print_elf_header_file_64 - Print elf header file 64 bits
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_elf_header_file_64(elf_struct_headers *elf_headers, int fd)
{
	unsigned long flags = 0;
	char *str_table = get_string_table(elf_headers, fd);

	if (elf_headers->e_64.e_type == ET_REL)
		flags |= HAS_RELOC;
	else if (elf_headers->e_64.e_type == ET_EXEC)
		flags |= EXEC_P;
	else if (elf_headers->e_64.e_type == ET_DYN)
		flags |= DYNAMIC;

	if (elf_headers->e_64.e_phnum > 0)
		flags |= D_PAGED;
	if (verification_section_64(elf_headers, str_table, ".symtab"))
		flags |= HAS_SYMS;
	if (verification_section_64(elf_headers, str_table, ".dynsym"))
		flags |= HAS_SYMS;
	if (verification_section_64(elf_headers, str_table, ".locals"))
		flags |= HAS_LOCALS;
	if (verification_section_64(elf_headers, str_table, ".lineno"))
		flags |= HAS_LINENO;
	if (verification_section_64(elf_headers, str_table, ".debug"))
		flags |= HAS_DEBUG;

	if (is_little_endian(elf_headers->e_64))
		printf("architecture: i386:x86-64, flags 0x%08lx:\n", flags);
	else
		printf("architecture: UNKNOWN!, flags 0x%08lx:\n", flags);
	print_file_flags(flags);
	printf("start address 0x%16.16lx\n", elf_headers->e_64.e_entry);

	free(str_table);
	return (0);
}

/**
 * verification_section_32 - verify is the section is in the file
 * @elf_headers: Elf headers
 * @str_table: string table
 * @sect: section to verify
 * Return: 1 on sucess, 0 otherwise
 */
int verification_section_32(elf_struct_headers *elf_headers, char *str_table,
	char *sect)
{
	unsigned int i = 0;

	for (i = 1; i < elf_headers->e_32.e_shnum; i++)
		if (!strcmp(&str_table[elf_headers->es_32[i].sh_name], sect))
			return (1);
	return (0);
}

/**
* print_elf_header_file_32 - Print elf header file 32 bits
* @elf_headers: Elf headers
* @fd: file descriptor
* Return: 0 on success, 1 otherwise
*/
int print_elf_header_file_32(elf_struct_headers *elf_headers, int fd)
{
	unsigned long flags = 0;
	char *str_table = get_string_table(elf_headers, fd);

	if (elf_headers->e_32.e_type == ET_REL)
		flags |= HAS_RELOC;
	else if (elf_headers->e_32.e_type == ET_EXEC)
		flags |= EXEC_P;
	else if (elf_headers->e_32.e_type == ET_DYN)
		flags |= DYNAMIC;

	if (elf_headers->e_32.e_phnum > 0)
		flags |= D_PAGED;
	if (verification_section_32(elf_headers, str_table, ".symtab"))
		flags |= HAS_SYMS;
	if (verification_section_32(elf_headers, str_table, ".dynsym"))
		flags |= HAS_SYMS;
	if (verification_section_32(elf_headers, str_table, ".locals"))
		flags |= HAS_LOCALS;
	if (verification_section_32(elf_headers, str_table, ".lineno"))
		flags |= HAS_LINENO;
	if (verification_section_32(elf_headers, str_table, ".debug"))
		flags |= HAS_DEBUG;

	if (is_little_endian(elf_headers->e_64))
		printf("architecture: i386, flags 0x%08lx:\n", flags);
	else
		printf("architecture: UNKNOWN!, flags 0x%08lx:\n", flags);
	print_file_flags(flags);
	printf("start address 0x%8.8lx\n",
		   (unsigned long)elf_headers->e_32.e_entry);

	free(str_table);
	return (0);
}
