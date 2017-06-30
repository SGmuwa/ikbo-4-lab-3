#include "enum_commands.h"

#ifndef _INC_STRING
#include <string>
#endif

/* Структура реализует хранение команды и аргумента. */
struct commands_value
{
	enum commands c; /* Команда */
	int v; /* Аргумент (например, для com_integer) */
};

/* Данная функция вернёт команду, которая первая в строке stdin. */
struct commands_value GetCommand(void)
{
	char buffer[32] = { '\0' };
	struct commands_value out = { 0 };
	scanf("%32s", buffer);
	if (buffer[0] != 0) /* Если buffer был заполнен */
	{
		/*if (buffer[0] != '*') GotoToAlphabet(input); /* Переходим на следующую команду */
		if (strcmp(buffer, "add") == 0)
		{ /* Не известно, можно ли в Си89 создавать константы структурного типа
		  http://port70.net/~nsz/c/c89/c89-draft.html#3.5.3 */
			return (struct commands_value) { com_add, 0 };
		}
		else if (strcmp(buffer, "show") == 0)
		{
			return (struct commands_value) { com_show, 0 };
		}
		else if (strcmp(buffer, "save") == 0)
		{
			return (struct commands_value) { com_save, 0 };
		}
		else if (strcmp(buffer, "load") == 0)
		{
			return (struct commands_value) { com_load, 0 };
		}
		else if (strcmp(buffer, "help") == 0)
		{
			return (struct commands_value) { com_help, 0 };
		}
		else if (strcmp(buffer, "quit") == 0)
		{
			return (struct commands_value) { com_quit, 0 };
		}
		else if (strcmp(buffer, "root") == 0)
		{
			return (struct commands_value) { com_root, 0 };
		}
		else if (strcmp(buffer, "node") == 0)
		{
			return (struct commands_value) { com_node, 0 };
		}
		else if (strcmp(buffer, "parent") == 0)
		{
			return (struct commands_value) { com_parent, 0 };
		}
		else if (strcmp(buffer, "sibling") == 0)
		{
			return (struct commands_value) { com_sibling, 0 };
		}
		else if (sscanf(buffer, "%d", &out.v) == 1)
		{
			out.c = com_integer;
			return out;
		}/*
		else if (strcmp(buffer, "*") == 0)
		{
			while (**input != '\n' && **input != EOF && **input != '\0') (*input)++;
			return com_comment;
		}*/
		else return (struct commands_value) { com_NaN, 0 };
	}
	else
	{
		return (struct commands_value) { com_NaN, -1 };
	}
}