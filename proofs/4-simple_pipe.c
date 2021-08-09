#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 10


int main(int argc, char *argv[])
{
	int pfd[2];	/* pipe file descriptors */
	char buf[BUF_SIZE];
	ssize_t numread;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		printf("bad usage\n");
		return (-1);
	}

	if (pipe(pfd) == -1) /* Create pipe */
	{
		printf("error in pipe\n");
		return(-1);
	}

	switch(fork()) {
	case -1:
		return (-1);
	case 0:				/* Child - reads from pipe */
		if (close(pfd[1]) == -1) /* Write end is unused */
		{
			printf("error closingwrite end of pipe in parent\n");
			return(-1);
		}
		for (;;)	/* Read data from pipe, echo on stdout */
		{
			numread = read(pfd[0], buf, BUF_SIZE);
			if (numread == -1)
			{
				printf("error read child\n");
				return(-1);
			}
			if (numread == 0)
				break;		/* End-of-file */
			if (write(STDOUT_FILENO, buf, numread) != numread)
			{
				printf("child - partial/failed write\n");
				return(-1);
			}

		}
		write(STDOUT_FILENO, "\n", 1);
		if (close(pfd[0]) == -1)
		{
			printf("error closing read end of pipe in child\n");
			return(-1);
		}
	default:	 /* Parent - writes to pipe */
		if (close(pfd[0]) == -1)
		{
			printf("error closing read end of pipe in parent\n");
			return (-1);
		}

		if (write(pfd[1], argv[1], (int) strlen(argv[1])) != (int) strlen(argv[1]))
		{
			printf("parent - partial/failed write\n");
			return(-1);
		}

		if (close(pfd[1]) == -1)
		{
			printf("error closing write end of pipe in parent\n");	/* Child will see EOF */
			return (-1);
		}
		wait(NULL);
		return(1);
	}


}
