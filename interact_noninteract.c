#include "shell.h"

/**
 * interactive - if shell is interactive, return true
 * @information: struct address
 *
 * Return: if shell is in interactive mode return 1, else return  0 
 **/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: c is the character to check
 * @delim: the string of the delimeter
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - This is the function that checks for alphabetic character
 *@c: The character to input is c
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - This function converts a string to an integer
 *@s: s is the string to be converted
 *Return: 0 if there is no numbers in string, convert number otherwise
 */

int _atoi(char *s)
{
	int x, signing = 1, flagging = 0, output;
	unsigned int result = 0;

	for (x = 0;  s[x] != '\0' && flagging != 2; x++)
	{
		if (s[x] == '-')
			signing *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flagging = 1;
			result *= 10;
			result += (s[x] - '0');
		}
		else if (flagging == 1)
			flagging = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

