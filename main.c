#include "shell.h"

/**
 * main - reads the user input and avaloidates it
 *
 * Return: status
 */
int main()
{
	char *tokens[10], *new = NULL;
	int i, ex = 0;
	bool state = true;
	path_t *_path = NULL;
	struct stat st;
	int (*execute)(char *cname, path_t *path);
    
	_path = create_path_list();
	/*print_listint_safe(_path);*/

	while (state)
	{
		i = 0, new = NULL;
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#cisfun$ ", 9);
		signal(SIGINT, handleCtrlc);

		buffer = get_line(_path);
		if (validate_line(_strlen(buffer), buffer) == 1)
			continue;

		buffer[_strlen(buffer) - 1] = '\0';
		tokens[i] = strtok(buffer, " ");

		while(tokens[i] != NULL)
			tokens[++i] = strtok(NULL, " ");

		if (stat(tokens[0], &st) == -1) {
			new = search_path(tokens[0], _path);
			if (new) {
				tokens[0] = new;
				fork_process(tokens);
				free(buffer);
				continue;
			}
			else {
				execute = search_in_builtins(tokens[0]);
				if (execute)
					ex = execute(tokens[0], _path);
			}
		}
		if (ex == 0)
			fork_process(tokens);
	}
	return (0);
}