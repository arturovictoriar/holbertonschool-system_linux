#ifndef HEADERLS
#define HEADERLS

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int count_characters(char *directory_to_show_ls);
char *add_bar_diagonal_end(char *str1);
char *concat_two_strings(char *str1, char *str2);
void free_memory_messages(char *chain_str);
int extra_info_ls(char *directory_to_show_ls, struct stat *buffer);
long get_size_file_directory(struct stat *buffer);
char *iniciatilize_string_permision(char *file_directory_permisions);
char *get_type_file_directory(struct stat *buffer, char *file_dire_permisions);
char *get_rwx_permisions(struct stat *buffer, char *file_directory_permisions);
char *get_time_file_directory(struct stat *buffer);
char *get_ugo_permisions(struct stat *buffer);
int ls_method(int argc, char **argv);
int error_alert(char *directory_to_show_ls);

#endif
