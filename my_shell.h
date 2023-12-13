#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/* Data structures */

typedef struct sep_list
{
	char separator;
	struct sep_list *next;
} sep_list;

typedef struct line_list
{
	char *line;
	int data;
	struct line_list *next;
} line_list;

typedef struct data_shell
{
	char **arguments;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
	char **av;
} data_shell;

typedef struct replacement_var
{
    int len_var;
    char *val;
    int len_val;
    struct replacement_var *next;
} r_var;

/* Function prototypes */

void handleSigint(int signalNumber);
char *readLine(int *isEof);
char **_reallocdp(char **ptr, size_t oldSize, size_t newSize);
char *_strtok(char *str, const char *delim);
extern char **_environ;
char *customRealloc(char *ptr, size_t oldSize, size_t newSize);
char *_strdup(const char *str);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
void _dprintf(int fd, const char *format, ...);
void shellLoop(data_shell *shellData);
int executeCommandLine(data_shell *shellData);
int (*getBuiltinFunction(const char *command))(data_shell *);
int executeShellCommand(data_shell *shellData);
void freeShellData(data_shell *shellData);
void initializeShellData(data_shell *shellData, char **arguments);
char *removeComment(char *input);
int checkSyntaxError(data_shell *datash, char *input);
char *replaceVariable(char *input, data_shell *datash);
int splitCommands(data_shell *datash, char *input);
void add_sep_node_end(sep_list **head, char separator);
line_list *add_line_node_end(line_list **line_list, char *line_text);
void free_sep_list(sep_list **head);
void free_line_list(line_list **line_list);
char *customRealloc(char *ptr, size_t oldSize, size_t newSize);
char *replace_input(r_var **variable_list, char *input_str, char *new_input_str, int new_length);
void reverse_string(char *str);
char *duplicate_string(const char *s);
int calculate_string_length(const char *s);
int compare_chars(char str[], const char *delim);
char *tokenize_string(char str[], const char *delim);
int is_digit_string(const char *s);
void handle_sigint(int signal_number);
char *swap_characters(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
int _strcmp(const char *s1, const char *s2);
char *intToString(int value);
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);
char *custom_strcat(char *destination, const char *source);
char *custom_strcpy(char *destination, char *source);
int custom_strcmp(char *str1, char *str2);
char *custom_strchr(char *str, char character);
int custom_strspn(char *str, char *accept);
int count_repeated_chars(char *input, int x);
int check_separator_error(char *input, int x, char last);
int find_first_char(char *input, int *x);
void print_syntax_error_msg(data_shell *datash, char *input, int x, int is_last);
int validate_syntax(data_shell *datash, char *input);
void calculate_builtin_length(const char *command);
void getError(data_shell *datash, int errnum);
char *get_error(data_shell *shell_data, int error_code);
void show_general_help(void);
void show_setenv_help(void);
void show_env_help(void);
void show_unsetenv_help(void);
void show_help(void);
void show_exit_help(void);
void show_cd_help(void);
void show_alias_help(void);
char *get_env_error(data_shell *shell_data);
char *get_path_error_126(data_shell *shell_data);
char *get_not_found_error(data_shell *shell_data);
char *get_exit_shell_error(data_shell *shell_data);
char *get_cd_error(data_shell *shell_data);
char *_strcat(char *dest, const char *src);
#endif /* MY_SHELL_H */

