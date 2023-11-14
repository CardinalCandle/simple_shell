#include "shell.h"

/**
 * _myhistory - displays the history list, one cmd by line,
 * preceded with line numbers, start at 0.
 * @info: struct of arguments
 *  Return: false
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (RET_SUCCESS);
}

/**
 * unset_alias - unsets alias to string
 * @info: param struct
 * @str: string alias
 * Return: 0 if success, 1 if error
 */
int unset_alias(info_t *info, char *str)
{
	char *p;
	char c;
	int res;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	res = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (res);
}

/**
 * set_alias - sets alias to string
 * @info: param struct
 * @str: str alias
 * Return: 0 if success, 1 if error
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
 * print_alias - prints alias string
 * @node: alias node
 * Return: 0 if success, 1 if error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *i = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (i = node->str; i <= p; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (RET_SUCCESS);
	}
	return (1);
}

/**
 * _myalias - implementation of the alias builtin
 * @info: Structure of arguments.
 * Return: 0
 */
int _myalias(info_t *info)
{
	int a;
	char *p = NULL;
	list_t *node = NULL;

	a = 0;
	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (RET_SUCCESS);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (RET_SUCCESS);
}
