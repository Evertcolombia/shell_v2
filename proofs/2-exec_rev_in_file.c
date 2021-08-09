#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ERROR(msg) do { perror(msg); exit(1); } while(0)

int main()
{
	int fd, status;
	pid_t child_pid;
	char *argv[2] = {"rev", NULL};

	fd = open("text", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd  == -1)
		return (-1);

	if (dup2(fd, STDOUT_FILENO) == -1)
		ERROR("dup2");

	close(fd);
	child_pid = fork();
	if (child_pid < 0)
		ERROR("fork");
	else if (child_pid == 0)
	{
		if (execve("/usr/bin/rev", argv, NULL) == -1)
			ERROR("execve");
	}
	waitpid(-1, &status, 0);
	return(1);
}
