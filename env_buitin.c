#include "shell.h"

/**
 * init_env - init enviroment with malloc
 *
 * Return: 0 on success -1 on error
 */
int init_env(void)
{
	char **new_env;
	int len_env = 0;


	for (len_env = 0; environ[len_env]; len_env++)
		;

	new_env = malloc(sizeof(environ) * (len_env + 1));
	if (new_env == NULL)
		return (-1);

	for (len_env = 0; environ[len_env]; len_env++)
	{
		new_env[len_env] = _calloc(_strlen(environ[len_env]) + 1, 1);
		if (new_env[len_env] == NULL)
			return (-1);
		
		_strncpy(new_env[len_env], environ[len_env],
			_strlen(environ[len_env]));
	}
	new_env[len_env] = 0;
	environ = new_env;
	return(0);
}

/**
 * free_env - frees the list at the end
 */
void free_env(void)
{
	int len_env = 0;

	for (len_env = 0; environ[len_env]; len_env++)
	{
		free(environ[len_env]);
		environ[len_env] = NULL;
	}
	free(environ);
}
