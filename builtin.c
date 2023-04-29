#include "shell.h"

/**
 * _myhistory - Shows the history list
 * @info: contains arguments prototype
 *
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - setting alias to string
 * @info: contains parameters
 * @str: the string alias
 *
 * Return: 0 when successful, 1 when there is an error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - setting alias to string
 * @info: parameter of alias
 * @str: the alias string
 *
 * Return: 0 when successful, 1 when there is an error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - printing alias string
 * @node: the  node
 *
 * Return: Always 0 when successful, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - acts like the other alias
 * @info: arguments and prototypes
 *
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		p = _strchr(info->argv[x], '=');
		if (p)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}

