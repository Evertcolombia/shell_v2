#include "shell.h"

int main()
{
	char *tokens[10], *new, *buffer = NULL;
	int i, len = 0;
	bool state = true;
	path_t *_path;
	struct stat st;

	_path = NULL;
	_path = create_path_list();
	print_listint_safe(_path);
	
	while (state)
	{
		i = 0;
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#cisfun$ ", 9);
		
		signal(SIGINT, handleCtrlc);
		buffer = get_line(_path);
		if (validate_line(_strlen(buffer), buffer) == 1)
			continue;
		len = _strlen(buffer);
		buffer[len - 1] = '\0';
		tokens[i] = strtok(buffer, " ");
		while(tokens[i] != NULL)
			tokens[++i] = strtok(NULL, " ");
		if (stat(tokens[0], &st) == -1) {
			new = search_path(tokens[0], _path);
			/*if (!new)
				execute = search_in_optionals();*/
			tokens[0] = new;
			fork_process(tokens);
			free(buffer);
			continue;
		}
		fork_process(tokens);
	}
	return (0);
}
