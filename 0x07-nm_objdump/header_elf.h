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

#define BFD_NO_FLAGS	0x00
#define HAS_RELOC	0x01
#define EXEC_P		0x02
#define HAS_LINENO	0x04
#define HAS_DEBUG	0x08
#define HAS_SYMS	0x10
#define HAS_LOCALS	0x20
#define DYNAMIC		0x40
#define WP_TEXT		0x80
#define D_PAGED		0x100

/**
 * struct elf_ESP_header - Elf header
 * @e_64: elf struct for 64 bits arquitecture
 * @e_32: elf struct for 32 bits arquitecture
 * @es_64: elf section struct for 64 bits arquitecture
 * @es_32: elf section struct for 32 bits arquitecture
 * @ep_64: elf section struct for 64 bits arquitecture
 * @ep_32: elf section struct for 32 bits arquitecture
 * @esy_64: elf section struct for 64 bits arquitecture
 * @esy_32: elf section struct for 32 bits arquitecture
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
	Elf64_Sym *esy_64;
	Elf32_Sym *esy_32;

} elf_struct_headers;

/*#####################Utils####################*/

/*utils_elf_1*/
int is_elf(Elf64_Ehdr e_64);
int is_64(Elf64_Ehdr e_64);
int is_little_endian(Elf64_Ehdr e_64);
int handle_arquitec(elf_struct_headers *elf_headers, int fd, char *prg);
int handle_data_format(elf_struct_headers *elf_headers);

/*utils_elf_section_1.c*/
int handle_section_header(elf_struct_headers *elf_headers, int fd);
int handle_symbol_section(elf_struct_headers *elf_headers, int fd, int i);
int clean_section_64_32(elf_struct_headers *elf_headers);
char *get_string_table(elf_struct_headers *elf_headers, int fd);
char *get_sym_string_table(elf_struct_headers *elf_headers, int fd, int i);

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

/*conver_endian_4*/
int convert_little_to_big_end_64_symbols(elf_struct_headers *elf_headers,
	unsigned int i);
int convert_little_to_big_end_32_symbols(elf_struct_headers *elf_headers,
	unsigned int i);

/*#####################ELF Symbol header#####################*/

/*print_elf_symbol_header_utils1.c*/
int print_elf_symbol_header(elf_struct_headers *e_file_header, int fd);
int print_64_symbol(elf_struct_headers *elf_headers, int fd);
int print_32_symbol(elf_struct_headers *elf_headers, int fd);
char *get_sstring_table(elf_struct_headers *elf_headers, int fd,
	char *str_table);

/*print_elf_section_content_utils1.c*/
int print_elf_section_content(elf_struct_headers *e_file_header, int fd);
int print_64_section_content(elf_struct_headers *elf_headers, int fd);
int section_content_64(elf_struct_headers *elf_headers, unsigned int i,
					   unsigned int j, unsigned char *content_s);
int print_32_section_content(elf_struct_headers *elf_headers, int fd);
int section_content_32(elf_struct_headers *elf_headers, unsigned int i,
					   unsigned int j, unsigned char *content_s);

/*utils_elf_symbol_1.c*/
char get_chr_type_symbol1_32(elf_struct_headers *elf_headers, int i);
char get_chr_type_symbol2_32(elf_struct_headers *elf_headers, int i);
char get_chr_type_symbol1_64(elf_struct_headers *elf_headers, int i);
char get_chr_type_symbol2_64(elf_struct_headers *elf_headers, int i);
int clean_symbol_64_32(elf_struct_headers *elf_headers);

/*utils_elf_section_content_1.c*/
unsigned char *get_section_content(elf_struct_headers *elf_headers, int fd,
	int i);
char *get_ftype(elf_struct_headers *elf_headers);

/*print_elf_header_file_1.c*/
int print_elf_header_file_64(elf_struct_headers *elf_headers, int fd);
int print_elf_header_file_32(elf_struct_headers *elf_headers, int fd);
int max_len_64(elf_struct_headers *elf_headers, unsigned int i);
int max_len_32(elf_struct_headers *elf_headers, unsigned int i);

#endif
