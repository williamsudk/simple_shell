#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

/* To read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* To command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* To convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Function for singly linked list
 * @num: Parameter for the number field
 * @str: Parameter for a string
 * @next: Parameter for points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Function that contains pseudo-arguements
 * allowing uniform prototype for function pointer struct
 * @arg: Parameter for a string generated from getline containing arguements
 * @argv: Parameter for an array of strings generated from arg
 * @path: Parameter for a string path for the current command
 * @argc: Parameter for the argument count
 * @line_count: Parameter for the error count
 * @err_num: Parameter for the error code for exit()s
 * @linecount_flag: Parameter for if on count this line of input
 * @fname: Parameter for the program filename
 * @env: Parameter for linked list local copy of environ
 * @environ: Parameter for custom modified copy of environ from LL env
 * @history: Parameter for the history node
 * @alias: Parameter for the alias node
 * @env_changed: Parameter for on if environ was changed
 * @status: Parameter to return status of the last exec'd command
 * @cmd_buf: Parameter for address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: Parameter for CMD_type ||, &&, ;
 * @readfd: Parameter for the fd from which to read line input
 * @histcount: Parameter for the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Function that contains a builtin string
 * @type: parameter for the builtin command flag
 * @func: Parameter for function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* for toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* for toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* for loophsh.c */
int loophsh(char **);

/* for toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* for toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* for toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* for toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* for toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* for toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* for toem_memory.c */
int bfree(void **);

/* for toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* for toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* for toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif
