#include "shell.h"

void fork_process(char *tokens[], char *buffer)
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
			perror("./shell");
	}
	waitpid(-1, &status, 0);
	free(buffer);
}
