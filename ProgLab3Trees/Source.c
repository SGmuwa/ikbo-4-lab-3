#define C89

#ifdef C89
#define _CRT_SECURE_NO_WARNINGS
#endif /* C89 */

#ifdef _CRT_SECURE_NO_WARNINGS
/*��� ������������� %s ��������� � ���������� ���� ������ � ���������� ���������� �������� � ���:
const char[], "%s", char[count], count*/
#define sscanf_u(x, y, ...) sscanf(x, y, ...)
#else
#define sscanf_u(x, y, ...) sscanf_s(x, y, ...)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ��������� ��� ������: �������. */
typedef struct Tree
{
	struct Tree * First; /* ������ ����� ������ */
	struct Tree * Second; /* ������ ����� ������ */
	signed value; /* �������� ����� �����. */
} Tree;

void main(void)
{
	return;
}

enum Commands
{
	NaN, /* ��� ����� */
	add, /* �������� �������� */
	show, /* �������� ������ */
	save, /* ��������� ��������� ��������� */
	load, /* ��������� ��������� ��������� */
	help, /* ������ */
	quit, /* ����� */
	root, /* ����������� ����: �������� */
	node, /* ���� */
	patern, /* ������� */
	sibling, /* �������� */
	integer /* ������������ �������� � ��������� ����� */
};

struct GCom { enum Commands com; signed vl; }

// �������� ������� �� ������������
GetCommand()
{
	static char * input = NULL;
	if (input == NULL)
	{
		input = (char*)malloc(sizeof(char) * 1024);
		*input = '\0';
	}
	if (input == "")
	{
		fgets(input, 1024, stdin);
	}
	if (strstr(input, "help") == input)
	{
		if (input[4] != ' ') strcpy_s(input, 1024, input + 4);
		else *input = '\0';
		return (struct GCom) { help, 0 };
	}
	else if (strstr(input, "add") == input)
	{
		if (input[3] != ' ') str�py(input, input + 3);
		else *input = '\0';
		return (struct GCom) { add, 0 };
	}
	else if (strstr(input, "save") == input)
	{
		if (input[4] != ' ') str�py(input, input + 4);
		else *input = '\0';
		return (struct GCom) { save, 0 };
	}
	else if (strstr(input, "load") == input)
	{
		if (input[4] != ' ') str�py(input, input + 4);
		else *input = '\0';
		return (struct GCom) { load, 0 };
	}
	else if (strstr(input, "quit") == input)
	{
		if (input[4] != ' ') str�py(input, input + 4);
		else *input = '\0';
		return (struct GCom) { quit, 0 };
	}
	else if (strstr(input, "root") == input)
	{
		if (input[4] != ' ') str�py(input, input + 4);
		else *input = '\0';
		return (struct GCom) { root, 0 };
	}
	else if (strstr(input, "node") == input)
	{
		if (input[4] != ' ') str�py(input, input + 4);
		else *input = '\0';
		return (struct GCom) { node, 0 };
	}
	else if (strstr(input, "patern") == input)
	{
		if (input[6] != ' ') str�py(input, input + 6);
		else *input = '\0';
		return (struct GCom) { patern, 0 };
	}
	else if (strstr(input, "sibling") == input)
	{
		if (input[7] != ' ') str�py(input, input + 7);
		else *input = '\0';
		return (struct GCom) { sibling, 0 };
	}
	else
	{
	    signed bf = 0;
		
		if (sscanf(input, "%d", &bf) > 0)
		{
			
			if (memchr(input, ' ', 1024))
			{

			}
			return (struct GCom) { integer, bf };
		}
		else
		{
			*input = '\0';
			return (struct GCom) { NaN, 0 };
		}

	}
}

void Interface()
{
	puts("����� ����������! ������� help ��� ������.");
}

Tree * MallocTree(signed value)
{
	Tree * buffer = (Tree*) malloc(sizeof(Tree));
	if(buffer != NULL) buffer->value = value;
	return buffer;
}

// int max lenght in char[]
#define iMAX_CH 36

// ���������� ��������� � char* ���
// countChar - ���������� ��������� �������� � output
// level - �������, ������� ��� �� �������� � ���������.
void TreeToString(Tree input, size_t countChar, char * output, unsigned level)
{
	if (output == NULL || countChar < 1) return; // ������ �� ������ �� ������������ ��� ������ ������ 

	size_t i = 0;

	for (; i < countChar && i < level; i++)
	{
		output[i] = '\t';
	}
	output += i;
	countChar -= i;
	i = 0;

	struct { size_t countStrInt; char str[iMAX_CH]; } iStr = { iMAX_CH, "" }; // ����������, ������� ������ ��������� � ���� string ������������� int � ������ ���������� ��.
	sprintf_s(iStr.str, iMAX_CH, "%d", input.value);
	iStr.countStrInt = strlen(iStr.str); // ��������� ����������� int � char*

	for (; i < countChar && i < iStr.countStrInt && i < iMAX_CH; i++)
	{
		output[i] = iStr.str[i];
	}
	if (i >= countChar) // ���� �� ������� �����, �� ��������� ������.
	{
		output[countChar - 1] = '\0';
	}
	else
	{
		output[i] = '\n';
	}
	if (i >= countChar) // ���� �� ������� �����, �� ��������� ������.
	{
		output[countChar - 1] = '\0';
	}
	output += i;
	countChar -= i;
	i = 0;

	if (input.First != NULL)
	{
		TreeToString(*input.First, countChar, output, level + 1);
	}
	if (input.Second != NULL)
	{
		TreeToString(*input.Second, countChar, output, level + 1);
	}
	return;

}

#undef iMAX_CH