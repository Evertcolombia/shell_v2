#ifndef SHELL_H
#define SHELL_H

/*Allowed Libraries*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

extern char **environ;
char *buffer;

typedef struct path_s {
	char *pathname;
	int len;
	struct path_s *next;
} path_t;

typedef struct cmd_s {
	char * cname;
	int (*func)(char *token, path_t *_path);
} cmd_t;


void handleCtrlc(int i);

char *get_line(path_t *head);
int validate_line(int len, char *buffer);
void tokenize_command(char *tokens[], char *buffer);

void fork_process(char *tokens[], path_t *_path);
path_t *create_path_list();

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);

path_t *add_node(path_t **head, char *pathname);
size_t print_listint_safe(path_t *head);
char *search_path(char *pathname, path_t *head);
size_t free_listint_safe(path_t **h);

int (*search_in_builtins(char *cname))(char *cname, path_t *_path);
int exit_builtin(char *cname, path_t *_path);
int init_env(void);
void free_env(void);

void *_calloc(unsigned int nmemb, unsigned int size);
#endif /* SHELL_H */
