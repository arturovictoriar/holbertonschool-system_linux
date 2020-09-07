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
 * @es_64: elf section struct for 64 bits arquitecture
 * @es_32: elf section struct for 32 bits arquitecture
 * @ep_64: elf section struct for 64 bits arquitecture
 * @ep_32: elf section struct for 32 bits arquitecture
 *
 * Description: Structures for handle elf headers
 */
typedef struct elf_ESP_header
{
	Elf64_Ehdr e_64;
	Elf32_Ehdr e_32;
	Elf64_Shdr *es_64;
	Elf32_Shdr *es_32;
	Elf64_Phdr *ep_64;
	Elf32_Phdr *ep_32;

} elf_struct_headers;

/*#####################Utils####################*/

/*utils_elf_1*/
int is_elf(Elf64_Ehdr e_64);
int is_64(Elf64_Ehdr e_64);
int is_little_endian(Elf64_Ehdr e_64);
int handle_arquitec(elf_struct_headers *elf_headers, int fd, char **av);
int handle_data_format(elf_struct_headers *elf_headers);

/*utils_elf_section_1.c*/
int handle_section_header(elf_struct_headers *elf_headers, int fd);
int clean_section_64_32(elf_struct_headers *elf_headers);
char *get_string_table(elf_struct_headers *elf_headers, int fd);

/*#####################Convert data format#################*/

/*convert_endian_1*/
int convert_little_to_big_end_64(elf_struct_headers *elf_headers);
int convert_little_to_big_end_32(elf_struct_headers *elf_headers);
uint16_t little_big_uint16_t(uint16_t x);

/*convert_endian_2*/
uint32_t little_big_uint32_t(uint32_t x);
Elf64_Addr little_big_Elf64_Addr(Elf64_Addr x);
Elf64_Off little_big_Elf64_Off(Elf64_Off x);
Elf32_Addr little_big_Elf32_Addr(Elf32_Addr x);
Elf32_Off little_big_Elf32_Off(Elf32_Off x);

/*convert_endian_3*/
uint64_t little_big_uint64_t(uint64_t x);
int convert_little_to_big_end_64_section(elf_struct_headers *elf_headers,
	unsigned int i);
int convert_little_to_big_end_32_section(elf_struct_headers *elf_headers,
	unsigned int i);
int convert_little_to_big_end_64_program(elf_struct_headers *elf_headers,
	unsigned int i);
int convert_little_to_big_end_32_program(elf_struct_headers *elf_headers,
	unsigned int i);

/*#####################ELF Section header#####################*/

/*print_elf_section_header_utils1.c*/
int print_elf_section_header(elf_struct_headers *e_file_header, int fd);
int print_64_section(elf_struct_headers *elf_headers, int fd);
int print_32_section(elf_struct_headers *elf_headers, int fd);
int print_footer_section(elf_struct_headers *elf_headers);
char *get_elf_section_flag(elf_struct_headers *elf_headers, int i);

/*print_elf_section_header_utils2.c*/
char *get_elf_section_type_64(elf_struct_headers *elf_headers, int i);
char *get_elf_section_type_32(elf_struct_headers *elf_headers, int i);
char *get_elf_section_type_64_1(elf_struct_headers *elf_headers, int i);
char *get_elf_section_type_32_1(elf_struct_headers *elf_headers, int i);

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

/*ELF Program header*/
#endif
