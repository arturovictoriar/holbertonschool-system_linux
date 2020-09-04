#ifndef ELF_HEADER
#define ELF_HEADER

/*Errors*/
#define ERR_USAGE "./#-hreadelf <file name>\n"
#define ERR_NOT_READ "%s: Error: Input file '%s' is not readable.\n"
#define ERR_FILE_NOT_FOUND "%s: Error: '%s': No such file\n"
#define ERR_NOT_ELF "%s: Error: Not an ELF file - it has the" \
					" wrong magic bytes at the start\n"

/*Standar libraries*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <elf.h>

/**
 * struct elf_ESP_header - Elf header
 * @e_64: elf struct for 64 bits arquitecture
 * @e_32: elf struct for 32 bits arquitecture
 *
 * Description: Structures for handle elf headers
 */
typedef struct elf_ESP_header
{
	Elf64_Ehdr e_64;
	Elf32_Ehdr e_32;
} elf_struct_headers;

/*ELF File header*/
int is_elf(Elf64_Ehdr e_64);
int print_elf_header(elf_struct_headers e_file_header);
int print_e_ident(Elf64_Ehdr e_64);
int print_e_class(Elf64_Ehdr e_64);
int print_e_data(Elf64_Ehdr e_64);
int print_e_version_d(Elf64_Ehdr e_64);
int print_e_osabi(Elf64_Ehdr e_64);
int print_e_abiversion(Elf64_Ehdr e_64);
int print_e_type(Elf64_Ehdr e_64);
int print_e_machine(Elf64_Ehdr e_64);
int print_e_machine_1(Elf64_Ehdr e_64);
int print_e_version(Elf64_Ehdr e_64);
int print_e_entry(Elf64_Ehdr e_64);
int print_e_phoff(Elf64_Ehdr e_64);
int print_e_shoff(Elf64_Ehdr e_64);
int print_e_flags(Elf64_Ehdr e_64);
int print_e_ehsize(Elf64_Ehdr e_64);
int print_e_phentsize(Elf64_Ehdr e_64);
int print_e_phnum(Elf64_Ehdr e_64);
int print_e_shentsize(Elf64_Ehdr e_64);
int print_e_shnum(Elf64_Ehdr e_64);
int print_e_shstrndx(Elf64_Ehdr e_64);

/*ELF Section header*/

/*ELF Program header*/
#endif
