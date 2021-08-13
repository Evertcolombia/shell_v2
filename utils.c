#include "shell.h"

/**
 * _strlen - get len of a string
 * @s: pointer to char
 *
 * Return: Len of the string
 */
int _strlen(char *s)
{
	char *cp = s;
	
	while (*cp != '\0')
		cp++;
	return (cp - s);
}

/**
 * _strcpy - makes a copy of a string
 * @dest: pointer to destiny
 * @src: source pointer
 *
 * Return: copied string
 */
char *_strcpy(char *dest, char *src)
{
	char *cp = dest;
	
	while ((*dest++ = *src++)) {
		if (*src == '\0')
			break;
	}
	dest = cp;
	return (dest);
}

/**
 * _strcmp - compare two strings
 * @s1: pointer to char
 * @s2: pointer to char
 *
 * Return: 0 on sucess
 */
int _strcmp(char *s1, char *s2)
{
	for (; *s1 == *s2; s1++, s2++)
	{
		if (*s1 == 61 || *s1 == '\0')
			return(0);
	}
	return(*s1 - *s2);
}

/**
 * _strdup - dups a string
 * @str: pointer to char
 *
 * Return: dup char
 */
char *_strdup(char *str)
{
	int a, i;
	char *p;
	a = 0;

	if (str == NULL)
		return (NULL);
	a = _strlen(str);
	p = malloc(sizeof(char) * a + 2);
	if (p == NULL)
		return (NULL);

	for (i = 0; i <= a; i++)
		p[i] = str[i];
	return (p);
}

/**
 * _strcat - concatenate two string
 * @dest: pointer to char
 * @src: pointer to char
 *
 * Return: destiny string
 */
char *_strcat(char *dest, char *src)
{
	char *head = dest;

	for (; *dest != '\0'; dest++)
		;
	while ((*dest++ = *src++))
		;
	dest = head;
	return (dest);
}

/**
 * _strncpy - merge  two strings
 *
 * @dest: second string
 * @src: first string
 * @n: limit number
 * Return: a pointer, to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != 0; i++)
		*(dest + i) = *(src + i);
	for (; i < n; i++)
		*(dest + i) = 0;
	return (dest);
}
