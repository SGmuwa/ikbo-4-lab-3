#pragma once

#ifndef _INC_TREE
#include "Tree.h"
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif

/* ����� ������ �� ������.
input - ������, ������� ���� ������� �� ������.
output - ����, ���� ���� �������. */
void Tree_IO_Print(const Tree * input, FILE * output)
{
	if (input == NULL)
	{
		printf("NULL\n");
		return;
	}
	size_t size = (size_t)Tree_CountNodes(input)*(40u + Tree_MaxLevel(input));
	char * buffer = (char *)malloc(size);
	if (buffer == NULL) return;
	Tree_ToString(*input, size, buffer, 0, ' ');
	fprintf(output, "%s\n", buffer);
	free(buffer);
}

/* ����� ���������� ������.
input - ������, ������� ���� ����������������.
output - �����, ���� ����� ��������� ����������. */
void Tree_IO_PrintStatistics(const Tree * input, FILE * output)
{
	unsigned char Heap = Tree_IsHeap(input);
	fprintf(output,
		"Leaves: %u\nInternal nodes: %u\nTotal number of nodes: %u\nTree is max or min heap: %s\n",
		Tree_CountLeaves(input),
		Tree_CountInternalNodes(input),
		Tree_CountNodes(input),
		Heap == 0 ? "No" :
		Heap == 1 ? "Max" :
		Heap == 2 ? "Min" :
		Heap == 3 ? "Yes" : "error");
}

Tree * _Tree_IO_ParseLevel(FILE * input, size_t level)
{
	/* 1. ���������� ���������� ������� */
	/* 2. ������� ����� */
	/* 3. ���� ������� ����� ����������, �� ������ ��������� Tr ��������� � ��������� ���� ������. */
	/* 4. lvls = ��������� ���������� ������� �� ��������� ����� */
	/* 5. ���� lvls < level + 1, �� ���� ���� �����. */
	/* 6. ���� ����������� �����, �� */
		/* mv = ���������� ��������, ������� ����� ��������� �����, ����� ��������� '\n' ��� '\r' */
		/* fSeekMove(input, -mv)*/
		/* ���� Tr.F == NULL, ��  */
			/* Tr.F = _Tree_IO_ParseLevel(input, level + 1) */
	/* 6. ���� �� ���� ������ ����������� ��� ��� �����, �� �������, ��� ��� ���� �����. */
	/* e. ���� ���� ��������, � �� �� ��������� �� ������ ������� ����, �� ��������� ������. */
	return NULL;
}

Tree * Tree_IO_Parse(FILE * input)
{
	return _Tree_IO_ParseLevel(input, 0u);
}