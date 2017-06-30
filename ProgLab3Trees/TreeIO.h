#pragma once

#ifndef _INC_TREE
#include "Tree.h"
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif

/* Вывод дерева на печать.
input - дерево, которое надо вывести на печать.
output - файл, куда надо вывести. */
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

/* Вывод статистики дерева.
input - дерево, которое надо проанализировать.
output - поток, куда нужно отправить результаты. */
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
	/* 1. Пропустить количество уровней */
	/* 2. Считать число */
	/* 3. Если считать число получилось, то создаём экземпляр Tr поддерева с значением этим числом. */
	/* 4. lvls = Посчитать количество уровней до следующей цифры */
	/* 5. Если lvls < level + 1, то этот узел готов. */
	/* 6. Если встретилось число, то */
		/* mv = количество символов, сколько нужно отступить назад, чтобы встретить '\n' или '\r' */
		/* fSeekMove(input, -mv)*/
		/* Если Tr.F == NULL, то  */
			/* Tr.F = _Tree_IO_ParseLevel(input, level + 1) */
	/* 6. Если на этом уровне встретилось уже две цифры, то считать, что это узел готов. */
	/* e. Если файл кончился, а мы не встретили ни одного прямого узла, то поддерево готово. */
	return NULL;
}

Tree * Tree_IO_Parse(FILE * input)
{
	return _Tree_IO_ParseLevel(input, 0u);
}