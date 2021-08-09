#include "shell.h"

int main()
{
	char *tokens[10];
	int i, len = 0;
	bool state = true;

	while (state)
	{
		i = 0;
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "#cisfun$ ", 9);
		
		signal(SIGINT, handleCtrlc);
		buffer = get_line();
		if (validate_line(_strlen(buffer), buffer) == 1)
			continue;
		len = _strlen(buffer);
		buffer[len - 1] = '\0';

		tokens[i] = strtok(buffer, " ");
		while(tokens[i] != NULL)
			tokens[++i] = strtok(NULL, " ");
		fork_process(tokens, buffer);
	}
	return (0);
}
