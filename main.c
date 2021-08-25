#include "shell.h"

/**
 * main - reads the user input and avaloidates it
 *
 * Return: status
 */
int main()
{
	char *tokens[10], *new = NULL;
	int ex = 0;
	bool state = true;
	path_t *_path = NULL;
	struct stat st;
	int (*execute)(char *cname, path_t *path);
	/*print_listint_safe(_path);*/

	signal(SIGINT, handleCtrlc);
	init_env(), _path = create_path_list();

	while (state)
	{
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#cisfun$ ", 9);

		buffer = get_line(_path);
		if (buffer == NULL)
			continue;

		tokenize_command(tokens, buffer);
		if (stat(tokens[0], &st) == -1) {
			new = search_path(tokens[0], _path);
			if (new) {
				tokens[0] = new, new = NULL;
				fork_process(tokens, _path);
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
			fork_process(tokens, _path);
	}
	return (0);
}
