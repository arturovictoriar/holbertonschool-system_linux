#ifndef HEADERLS
#define HEADERLS

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int count_characters(char *directory_to_show_ls);
char *add_bar_diagonal_end(char *str1);
char *concat_two_strings(char *str1, char *str2);
void free_memory_messages(char *chain_str);
int extra_info_ls(char *directory_to_show_ls, struct stat *buffer);
int ls_method(int argc, char **argv);
int error_alert(char *directory_to_show_ls);

#endif
