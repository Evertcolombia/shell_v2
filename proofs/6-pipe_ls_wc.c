#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int pfd[2];
	char *co[2] = {"ls", NULL};
	char *cos[3] = {"wc", "-l", NULL};

	(void) argc;
	(void) *argv;
	if (pipe(pfd) == -1)
	{
		printf("error creat pipe\n");
		return (-1);
	}

	switch (fork())
	{
		case -1:
			exit(1);

		case 0:		/* First child: exec 'ls' to write to pipe */
			if (close(pfd[0]) == -1)
			{
				printf("errorin close wread end\n");
				exit(1);
			}
			/* Duplicate stdout on write end of pipe; close duplicated descriptor */
			if (pfd[1] != STDOUT_FILENO) {
				if (dup2(pfd[1], STDOUT_FILENO) == -1)
				{
					printf("error in dup2 \n");
					exit(1);
				}
				if (close(pfd[1]) == -1)
				{
					printf("errorin write end\n");
					exit(1);
				}
				if (execve("/usr/bin/ls", co, NULL) == -1)
					exit(1);
			}
		default:
			break;

	}

	switch (fork())
	{
		case -1:
			exit(1);
		case 0:	/* Second child: exec 'wc' to read from pipe */
			if (close(pfd[1]) == -1)
			{
				 printf("errorin write end\n");
				 exit(1);
			}
		      /* Duplicate stdin on read end of pipe; close duplicated descriptor */
			if (pfd[0] != STDIN_FILENO) {
				if (dup2(pfd[0], STDIN_FILENO) == -1)
					exit(1);
				if (close(pfd[0]) == -1)
					exit(1);
			}
			if (execve("/usr/bin/wc", cos, NULL) == -1)
				exit(1);
		default:
			break;
	}

	/* Parent closes unused file descriptors for pipe, and waits for children */
	if (close(pfd[0]) == -1)
	{
		printf("errorin close wread end\n");
		return (-1);
	}

	if (close(pfd[1]) == -1)
		return(-1);

	if (wait(NULL) == -1)
		return(-1);
	if (wait(NULL) == -1)
		return(-1);
	exit(EXIT_SUCCESS);
	

}
