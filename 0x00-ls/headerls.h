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
#include <pwd.h>
#include <grp.h>

/**
  * struct tag - Struct tag
  *
  * @option: The option tag
  * @function: The function associated
  */
typedef struct tag
{
	char *option;
	int (*function)(struct dirent *, char *, char **);
} tag_option;

int count_characters(char *directory_to_show_ls);
char *add_bar_diagonal_end(char *str1);
char *concat_two_strings(char *str1, char *str2);
void free_memory_messages(char *chain_str);
int extra_info_ls(char *directory_to_show_ls, struct stat *buffer);
long get_size_file_directory(struct stat *buffer);
char *iniciatilize_string_permision(char *file_directory_permisions);
char *get_type_file_directory(struct stat *buffer, char *file_dire_permisions);
char *get_rwx_permisions(struct stat *buffer, char *file_directory_permisions);
char *get_short_date(char *full_date);
char *get_time_file_directory(struct stat *buffer);
char *get_user_id_file_directory(struct stat *buffer);
char *get_group_id_file_directory(struct stat *buffer);
char *get_ugo_permisions(struct stat *buffer);
void error_malloc(void);
char *g_name(int f, int, char **, int index);
int ls_metho(int argc, char **argv, int (*f)(struct dirent *, char *, char**));
int error_alert(char *directory_to_show_ls);
int error_option(char *option_tag_ls);
int ls_basic(struct dirent *read, char *directory_to_show_ls, char **ls_c_ms);
int ls_options(struct dirent *read, char *directory_to_show_ls, char **ls_c_);
int (*check_options_ok(int argc, char **argv))();
int ls_message_generator(char *d_f_name, char **ls_complet_message);
int choose_value_start(int argc, int (*f)(struct dirent *, char *, char **));
int add_name_dir(char *d_f_name, char **ls_complet_message);
int add_list_f_d(char *d_f_name, char **ls_complet_message);
int mul_name(int argc, int s_num, int i, char **argv, char **ls_c, int f_s_c);

#endif
