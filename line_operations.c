#include "shell.h"

char *get_line(path_t *head)
{
	size_t size = 0;

	fflush(stdin);
	if (getline(&buffer, &size, stdin) == EOF)
	{
		free(buffer);
		free_listint_safe(&head);
		free_env();
		exit(0);
	}

	if (validate_line(_strlen(buffer), buffer) == 1)
		return (NULL);

	buffer[_strlen(buffer) - 1] = '\0';
	return (buffer);
}

int validate_line(int len, char *buffer)
{
	if (buffer == NULL) {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return(1);
	}
	if (len  < 0) {
		free(buffer);
		exit(1);
	}
	else if (len  == 1 && *buffer == 10) {
		free(buffer);
		return (len);
	}
	return(0);
}

void tokenize_command(char *tokens[], char *buffer)
{
	int i = 0;

	tokens[i] = strtok(buffer, " ");
	while(tokens[i] != NULL)
		tokens[++i] = strtok(NULL, " ");
}
