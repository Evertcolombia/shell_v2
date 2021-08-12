#include "shell.h"

/**
 * search_in_builtins - search for builtin commands
 * @cname: command name
 *
 * Return Function Pointer or NULL
 */
int (*search_in_builtins(char *cname))(char *cname, path_t *_path)
{
	int i = 0;

	cmd_t builtins[] = {
	{"exit", exit_builtin}
	};

	while (i < 1) {
	if (_strcmp(cname, builtins[i].cname) == 0)
		return (builtins[i].func);
	i++;
	}
	return (NULL);
}

/**
 * exit_builtin - exit built-in 
 * @cname: the name of the command
 * @_path: environment linked list
 *
 * Return: None
 */
int exit_builtin(char *cname, path_t *_path)
{
	(void) cname;

	free_listint_safe(&_path);
	free(buffer);
	exit(1);
}