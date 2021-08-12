#include "shell.h"
/**
 * handleCtrlc - evit use Ctrl + C in our shell
 * @i: is the status
 */
void handleCtrlc(int i)
{
	(void) i;

	/*write(STDOUT_FILENO, "#chanda$ ", 9);
	fflush(stdout);*/
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(1);
}
