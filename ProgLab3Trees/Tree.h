#pragma once

#define _INC_TREE

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif

/* ��������� ��� ������: �������.
��� ��������� � �������� int. */
typedef struct Tree
{
	struct Tree * First; /* ������ ����� ������ */
	struct Tree * Second; /* ������ ����� ������ */
	int value; /* �������� ����� �����. */
} Tree;

/* ������ � ������ ��������� ���� ������.
value - �������� ����. */
Tree * Tree_Malloc(int value)
{
	Tree * buffer = (Tree*)malloc(sizeof(Tree));
	if (buffer != NULL)
	{
		buffer->value = value;
		buffer->First = buffer->Second = NULL;
	}
	return buffer;
}

/* ������� ������ �� ������ ������ � ��� �������. */
void Tree_Free(Tree * target)
{
	if (target == NULL) return;
	if (target->First != NULL)
	{
		Tree_Free(target->First);
		free(target->First);
	}
	if (target->Second != NULL)
	{
		Tree_Free(target->Second);
		free(target->Second);
	}
}

/* ������������ ����� ������������� ������ ����� � char
��������������, ��� ������ ������ ����� 2^128 �����. */
#define iMAX_CH 40

/* ���������� ��������� � char* ���
countChar - ���������� ��������� �������� � output
output - ��������� �� �����
level - �������, ������� ��� �� �������� � ���������.*/
size_t Tree_ToString(const Tree input, size_t countChar, char * output, unsigned level)
{
	size_t i = 0u;
	size_t countprintT = 0u;
	if (output == NULL || countChar < 1u)
		return 0u; /* ������ �� ������ �� ������������ ��� ������ ������ */

	for (; i < countChar && i < level; i++)
	{
		output[i] = ' ';
	}
	output += i;
	countChar -= i;
	countprintT = i;
	i = 0u;
	struct
	{ 
		size_t countStrInt; /* ������������ ��� ���������� ���������� �������� � sprintf */
		char str[iMAX_CH]; /* ���� �������� (����������� ������) */
	} iStr = { sizeof(iStr.str), "" }; /* ����������, ������� ������ ��������� � ���� string ������������� int � ������ ���������� ��. */
#ifdef _CRT_SECURE_NO_WARNINGS
	sprintf(iStr.str, "%d", input.value);
#else
	sprintf_s(iStr.str, sizeof(iStr.str), "%d", input.value);
#endif
	iStr.countStrInt = strlen(iStr.str); /* ��������� ����������� int � char* */

	for (; i < countChar && i < iStr.countStrInt && i < iMAX_CH; i++)
	{
		output[i] = iStr.str[i];
	}
	if (i >= countChar) /* ���� �� ������� �����, �� ��������� ������. */
	{
		output[countChar - 1u] = '\0';
	}
	else
	{
		output[i++] = '\n';
	}
	countChar += countprintT;
	output -= countprintT;
	i += countprintT;
	if (input.First != NULL)
	{
		i += Tree_ToString(*input.First, countChar - i, output + i, level + 1);
	}
	if (input.Second != NULL)
	{
		i += Tree_ToString(*input.Second, countChar - i, output + i, level + 1);
	}
	
	if (level == 0u && i < countChar) output[i] = 0;
	return i;

}

/* ���������� ���������� ������� ������. */
unsigned int Tree_CountLeaves(const Tree * input)
{
	return input == NULL ? 0u :
		input->Second == NULL && input->First == NULL ? 1u :
		Tree_CountLeaves(input->First) + Tree_CountLeaves(input->Second);
}

/* ���������� ���������� ���������� ����� ������. */
unsigned int Tree_CountInternalNodes(const Tree * input)
{
	return input == NULL ? 0u :
		input->Second == NULL && input->First == NULL ? 0u :
		1u + Tree_CountInternalNodes(input->First) + Tree_CountInternalNodes(input->Second);
}

/* ���������� ���������� ���� ����� ������. */
unsigned int Tree_CountNodes(const Tree * input)
{
	return input != NULL ?
		1u + Tree_CountNodes(input->First) + Tree_CountNodes(input->Second) :
		0u;
}

unsigned int Tree_MaxLevel(const Tree * input)
{
	unsigned int bM[2] = { 0 }; /* buffer Max */
	return input == NULL ? 0u :
		(bM[0] = Tree_MaxLevel(input->First)) > (bM[1] = Tree_MaxLevel(input->Second)) ? bM[0] + 1u :
		bM[1] + 1u;

}

/* ����� ������ �� ������. */
void Tree_Print(const Tree * input, FILE * output)
{
	if (input == NULL)
	{
		printf("NULL\n");
		return;
	}
	size_t size = (size_t)Tree_CountNodes(input)*(40u + Tree_MaxLevel(input));
	char * buffer = (char *)malloc(size);
	if (buffer == NULL) return;
	Tree_ToString(*input, size, buffer, 0);
	fprintf(output, "%s\n", buffer);
	free(buffer);
}

/* �������� �� ������, �������� �� ��� ������ �����
0 - ���
1 - ���� ���������
2 - ���� ��������
3 - ������������� ����*/
unsigned char Tree_IsHeap(Tree * root)
{
	if (root == NULL || (root->First == NULL && root->Second == NULL))
		return 0x3u; /* ���� ��� ������ ������, �� ��� ������������� */
	if (((root->First == NULL) ^ (root->First != NULL && root->value > root->First->value))
		&& ((root->Second == NULL) ^ (root->Second != NULL && root->value > root->Second->value)))
		return 0x1u & Tree_IsHeap(root->First) & Tree_IsHeap(root->Second);
	else if (((root->First == NULL) ^ (root->First != NULL && root->value < root->First->value))
		&& ((root->Second == NULL) ^ (root->Second != NULL && root->value < root->Second->value)))
		return 0x2u & Tree_IsHeap(root->First) & Tree_IsHeap(root->Second);
	else return 0x0u;
/*
� - ������ ������ ������
� - ������ ������ ������������� ������� � �� �� ������
� - ������ ������ ������
� - ������ ������ ������������� ������� � �� �� ������

����
0000
0001
0010
0011 x
0100
0101 +
0110 +
0111 x
1000
1001 +
1010 +
1011 x
1100 x
1101 x
1110 x
1111 x

0101 +
0110 +
1001 +
1010 +

return:
01
x1
x1
*/
}

/* ����� ���������� ������ */
void Tree_PrintStatistics(Tree * input, FILE * output)
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

#include "TreeSearch.h"