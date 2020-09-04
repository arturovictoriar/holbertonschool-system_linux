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

/*#####################Utils####################*/

/*utils_elf_1*/
int is_elf(Elf64_Ehdr e_64);
int is_64(Elf64_Ehdr e_64);
int handle_arqui_endi_file(elf_struct_headers *elf_headers, int fd, char **av);

/*#####################ELF File header#####################*/

/*print_elf_header_utils1*/
int print_elf_header(elf_struct_headers e_file_header);
int print_e_ident(elf_struct_headers e_file_header);
int print_e_class(elf_struct_headers e_file_header);
int print_e_data(elf_struct_headers e_file_header);

/*print_elf_header_utils2*/
int print_e_version_d(elf_struct_headers e_file_header);
int print_e_osabi(elf_struct_headers e_file_header);
int print_e_abiversion(elf_struct_headers e_file_header);
int print_e_type(elf_struct_headers e_file_header);

/*print_elf_header_utils3*/
int print_e_machine(elf_struct_headers e_file_header);
int print_e_machine_1(elf_struct_headers e_file_header);
int print_e_version(elf_struct_headers e_file_header);
int print_e_entry(elf_struct_headers e_file_header);
int print_e_phoff(elf_struct_headers e_file_header);

/*print_elf_header_utils4*/
int print_e_shoff(elf_struct_headers e_file_header);
int print_e_flags(elf_struct_headers e_file_header);
int print_e_ehsize(elf_struct_headers e_file_header);
int print_e_phentsize(elf_struct_headers e_file_header);
int print_e_phnum(elf_struct_headers e_file_header);

/*print_elf_header_utils5*/
int print_e_shentsize(elf_struct_headers e_file_header);
int print_e_shnum(elf_struct_headers e_file_header);
int print_e_shstrndx(elf_struct_headers e_file_header);

/*ELF Section header*/

/*ELF Program header*/
#endif
