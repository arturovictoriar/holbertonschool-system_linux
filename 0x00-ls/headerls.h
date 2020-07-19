#ifndef HEADERLS
#define HEADERLS

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
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
	int (*function)(struct dirent *, char *, char **, char **);
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
int ls_metho(int argc, char **argv, char **,
	int (*f)(struct dirent *, char *, char**, char **));
int e_alert(char *, char **, char **,
	int (*f)(struct dirent *, char *, char**, char **));
int error_option(char *option_tag_ls);
int ls_basic(struct dirent *read,
	char *directory_to_show_ls, char **ls_c_ms, char **);
int ls_l_flg(struct dirent *read,
	char *directory_to_show_ls, char **ls_c_, char **);
int (*check_options_ok(int argc, char **argv, char **))();
int ls_message_generator(char *d_f_name, char **ls_complet_message);
int choose_value_start(int argc,
	int (*f)(struct dirent *, char *, char **, char **));
int add_name_dir(char *d_f_name, char **ls_complet_message);
int add_list_f_d(char *d_f_name, char **ls_complet_message);
int mul_name(int argc, int s_num, int i, char **argv, char **ls_c, int f_s_c);
int print_list_ls(char **ls_complete_message, char **is_file, char **h_permi);
int ls_1_flg(struct dirent *read,
	char *directory_to_show_ls, char **ls_c_mes, char **);
int ls_1_flag_m_generetor(char *d_f_name, char **ls_complet_message);
int _strcmp(char *s1, char *s2);
int get_options(char **argv, int i_argv, char **, tag_option *);
int ls_a_flg(struct dirent *read,
	char *directory_to_show_ls, char **ls_c_mes, char **);
int set_all_flgs(char **option_tag_ls, char *op);
char *get_proper_basic_dir(int argc, char **argv, int index);
char *get_proper_option_dir(int argc, char **argv, int index);
int print_all_output(char **is_file, char **h_permi,
	char **ls_complete_message, char **option_tag_ls, int error_flag1);
int ls_A_flg(struct dirent *read, char *directory_to_show_ls,
	char **ls_c_mes, char **option_tag_ls);
tag_option *all_hls_opt(void);
char *get_more_info_dir(struct dirent *read, char *directory_to_show_ls);
char *paste_options(char *ugo_permision, char *user_id, char *group_id,
	long size_f_or_d, char *time, char *d_name);

#endif
