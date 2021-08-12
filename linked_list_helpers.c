#include "shell.h"

/**
 * add_node - add a node to the enviromen link list
 * @head: double pointer to the list head
 * @pathname: name of the path to env var
 *
 * Return: new node or Null
 */
path_t *add_node(path_t **head, char *pathname)
{
	path_t *new;

	if (head == NULL) {
		perror("Error");
		exit(1);
	}
	new = (path_t *) malloc(sizeof(path_t));
	if (new == NULL) {
		perror("Error");
		exit(1);
	}

	new->pathname = _strdup(pathname);
	new->len = _strlen(new->pathname);
	new->next = *head, *head = new;
	return (new);
}

/**
 * search_path - search for a path in the linked
 * @pathname: name of the path to search
 * @head: head of the linked list
 *
 * Return: pointer to new command 
 */
char *search_path(char *pathname, path_t *head)
{
	char *copy = NULL, *new;
	struct stat st;
	int len = 0;
	
	while (head != NULL)
	{
		copy = _strdup(head->pathname);
		copy = _strcat(copy, "/");
		len = (head->len + 1) + (_strlen(pathname) + 1);
		new = _calloc(len, sizeof(char));
		new = _strcat(_strcpy(new, copy), pathname);
		free(copy);
		if (stat(new, &st) == 0)
			return (new);
		head = head->next;
		free(new);
	}
	return (NULL);
}

/**
 * print_listint_safe - print linked list safety
 * @head: head of the linked list
 *
 * Return: size of the list
 */
size_t print_listint_safe(path_t *head)
{
	size_t count = 0;

	while (head != NULL)
	{
		printf("[%p] %s\n", (void *)head, head->pathname);
		count++;
		if ((head->next) >= head)
		{
			printf("-> [%p] %s\n", (void *)head->next, head->next->pathname);
			return (count);
		}
		head = head->next;
	}
	return (count);
}

/**
 * free_listint_safe - frees a linked list
 * @h: head of the linked list
 *
 * Return: size of the freesed linked list
 */
size_t free_listint_safe(path_t **h)
{
	size_t count = 0;
	path_t *tmp = NULL;

	while (*h != NULL)
	{
		count++;
		tmp = *h;
		*h = (*h)->next;
				free(tmp->pathname);
		if ((tmp->next) >= tmp)
		{
			*h = NULL;
			return (count);
		}
				free(tmp);
	}
	*h = NULL;
	return (count);
}