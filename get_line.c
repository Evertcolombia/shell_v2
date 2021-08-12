#include "shell.h"

char *get_line(path_t *head)
{
	size_t size = 0;

	fflush(stdin);
	if (getline(&buffer, &size, stdin) == EOF)
	{
		free(buffer);
		free_listint_safe(&head);
		exit(0);
	}
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
