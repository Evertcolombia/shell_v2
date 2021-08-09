#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int pfd[2];
	int j, dummy;


	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s sleep-time...\n", argv[0]);
		return (-1);
	}

	printf("Parent started\n");

	if (pipe(pfd) == -1)
	{
		printf("error in pipe\n");
		return(-1);
	}

	for (j = 0; j < argc; j++)
	{
		switch(fork())
		{
			case -1:
				return (-1);
			case 0: 		/* child */
				if (close(pfd[0] == -1)) {
					printf("error closingwrite end of pipe in parent\n");
					return (-1);
				}
				/* Child does some work, and lets parent know it's done */
				sleep(3);
				printf("Child\n");

				if (close(pfd[1]) == -1)
				{
					printf("errorin close read end\n");
					return (-1);
				}

				/* Child now carries on to do other things... */
				exit(EXIT_SUCCESS);
			default:
				break;
		}

	}

	/* Parent comes here; close write end of pipe so we can see EOF */

	if (close(pfd[1]) == -1) 	/* Write end is unused */
	{
		 printf("errorin close write end\n");
		 return (-1);
	}

	/* Parent may do other work, then synchronizes with children */
	if (read(pfd[0], &dummy, 1) != 0)
	{
		printf("another errror\n");
		return (-1);
	}
	printf("Parent ready to go\n");
	exit(EXIT_SUCCESS);
}
