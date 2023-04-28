#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFF 1024
#define WRITE_BUFF 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define COMMAND_NORM	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAIN	3

/* for number_conversion() */
#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2

/* 1 if using system getline() */
#define USEGETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct slist - singly linked list
 * @num: number field
 * @str: a string
 * @next: pointer to the next node
 */
typedef struct slist
{
	int num;
	char *str;
	struct slist *next;
} list_of_items;

/**
 * struct createPassInfo - holds arguments for passing into a function,
 * enabling a consistent prototype for a function pointer structure.
 * @arg: a string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @path:  the current command string path
 * @argc: the argument count
 * @line_counter: the error count
 * @error_num: error code for exit()
 * @linecounterflag: if true count this line
 * @filename: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ
 * @history: the history node
 * @alias: the alias node
 * @environ_changed: on when environ change
 * @status: return status of the last executed command
 * @command_buff: address of pointer to command_buff, on if chaining
 * @command_buff_type: COMMAND_type ||, &&, ;
 * @input_file_descriptor: the file discriptor from which to read line input
 * @historycounter: the history line number count
 */
typedef struct createPassInfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_counter;
	int or;
	int linecounterflag;
	char *filename;
	list_of_items *env;
	list_of_items *history;
	list_of_items *alias;
	char **environ;
	int environ_changed;
	int status;

	char **command_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int command_buff_type; /* COMMAND_type ||, &&, ; */
	int input_file_descriptor;
	int historycounter;
} info_t;

#define INITIALIZE_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin_functions - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin_functions
{
	char *type;
	int (*func)(info_t *);
} builtin_functions_table;

/* sh_loop.c */
int hsh(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* toem_parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loop_hash_table.c */
int loop_hash_table(char **);

/* errors.c */
void error_print_string(char *);
int error_print_char(char);
int write_char_to_fd(char c, int fd);
int write_string_to_fd(char *str, int fd);

/* string.c */
int str_length(char *);
int str_compare(char *, char *);
char *str_starts_with(const char *, const char *);
char *str_concatenate(char *, char *);

/* string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void _print_string(char *);
int _print_char(char);

/* exits.c */
char *copy_n_chars(char *, char *, int);
char *concat_n_chars(char *, char *, int);
char *find_char(char *, char);

/* tokenizer.c */
char **split_string(char *, char *);
char **split_string_delim(char *, char);

/* realloc.c */
char *_mem_fill(char *, char, unsigned int);
void free_strings(char **);
void *_reallocate(void *, unsigned int, unsigned int);

/* memory.c */
int mem_free(void **);

/* atoi.c */
int interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int _atoi(char *);

/* errors1.c */
int _atoierror(char *);
void print_errors(info_t *, char *);
int print_digits(int, int);
char *number_conversion(long int, int, int);
void rm_comment(char *);

/* builtin_functions.c */
int _exit_shell(info_t *);
int _change_directory(info_t *);
int _display_help(info_t *);

/* builtin_functions1.c */
int history_builtin(info_t *);
int alias_builtin(info_t *);

/*getline.c */
ssize_t read_input(info_t *);
int get_line(info_t *, char **, size_t *);
void handle_sigint(int);

/* getinfo.c */
void initialize_info(info_t *);
void fill_info(info_t *, char **);
void _info_free(info_t *, int);

/* environ.c */
char *get_env_var(info_t *, const char *);
int print_env(info_t *);
int set_env_var(info_t *);
int unset_env_var(info_t *);
int create_env_list(info_t *);

/* env_var.c */
char **get_environment_variables(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* history.c */
char *getHistoryFilePath(info_t *info);
int writeHistoryToFile(info_t *info);
int readHistoryFromFile(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistoryEntries(info_t *info);

/* lists.c */
list_of_items *add_new_node(list_of_items **, const char *, int);
list_of_items *add_end_node(list_of_items **, const char *, int);
size_t print_mylist_of_strings(const list_of_items *);
int del_node_at_index(list_of_items **, unsigned int);
void free_mylist(list_of_items **);

/* lists1.c */
size_t lenth_of_list(const list_of_items *);
char **str_list_of_items(list_of_items *);
size_t print_mylist(const list_of_items *);
list_of_items *node_starts_with(list_of_items *, char *, char);
ssize_t get_index_of_node(list_of_items *, list_of_items *);

/* vars.c */
int is_variable_chain(info_t *, char *, size_t *);
void validate_variable_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replacement(info_t *);
int variables_replacement(info_t *);
int str_replacement(char **, char *);

#endif
