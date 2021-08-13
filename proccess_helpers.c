#include "shell.h"

void fork_process(char *tokens[], path_t *_path)
{
	int status;
	pid_t child_pid;
	child_pid = fork();
	
	if (child_pid < 0) {
		perror("./shell");
		exit(0);
	}
	else if (child_pid == 0) {
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			free_listint_safe(&_path);
			free(buffer);
			_exit(2);
		}
	}
	waitpid(-1, &status, 0);
	free(tokens[0]);
}

path_t *create_path_list()
{
	char **copy = environ, *token = NULL;
	path_t *head;

	head = NULL;
	for (; *copy != NULL; copy++) {
		if (_strcmp(*copy, "PATH=") == 0)
		{
			token = strtok(*copy, "=");
			while(token != NULL) {
				token = strtok(NULL, ":");
				if (token)
					add_node(&head, token);
			}
		}
	}

	return (head);
}
