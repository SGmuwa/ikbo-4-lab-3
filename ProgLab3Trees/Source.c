#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif /* _INC_STDIO */

#ifndef _INC_STRING
#include <string.h>
#endif /* _INC_STRING */

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

/* EFAULT ������������ ����� */
/* EACCES ����� � ������� */

errno_t strcpy_u(char * to, size_t count, const char * from)
{
	if (to == NULL || from == NULL) return EFAULT;
#ifdef _CRT_SECURE_NO_WARNINGS
	return strcpy(to, from) == to ? 0 : EACCES;
#else
	return strcpy_s(to, (rsize_t)count, from);
#endif
}

#include "GetCommands.h"

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


void Interface(void)
{
	puts("����� ����������! ������� help ��� ������.");
}

Tree * MallocTree(signed value)
{
	Tree * buffer = (Tree*) malloc(sizeof(Tree));
	if(buffer != NULL) buffer->value = value;
	return buffer;
}

/* int max lenght in char[] */
#define iMAX_CH 36

/* ���������� ��������� � char* ���
countChar - ���������� ��������� �������� � output
level - �������, ������� ��� �� �������� � ���������. */
void TreeToString(Tree input, size_t countChar, char * output, unsigned level)
{
	if (output == NULL || countChar < 1)
		return; /* ������ �� ������ �� ������������ ��� ������ ������ */

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
