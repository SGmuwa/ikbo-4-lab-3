#pragma once

#ifndef _INC_TREE
#include "Tree.h"
#endif

#define TSDD Tree_Search_DisorderedData

/* Реализаует рекурсивный поиск по неупорядоченным данным.
root - корень дерева, с которого надо начать поиск.
value - значение, которое следует найти в дереве. */
Tree * Tree_Search_DisorderedData(Tree * root, int value)
{
	Tree * out;
	if (root == NULL) return NULL;
	if (root->value == value) return root;
	return (out = TSDD(root->First, value)) == NULL ?
		TSDD(root->Second, value) : out;
}
#undef TSDD
#define TSDDFP Tree_Search_DisorderedDataFreeParent

/* Реализаует рекурсивный поиск по ключу. Фильтр: хотя бы одна связь вниз - свободная.
root - корень дерева, с которого надо начать поиск.
value - значение, которое следует найти в дереве. */
Tree * Tree_Search_DisorderedDataFreeParent(Tree * root, int value)
{
	Tree * out;
	if (root == NULL) return NULL;
	if (root->value == value && (root->First == NULL || root->Second == NULL)) return root;
	return (out = TSDDFP(root->First, value)) == NULL ?
		TSDDFP(root->Second, value) : out;
}

#undef TSDDFP
#define TSDDFS Tree_Search_DisorderedDataFreeSibling

/* Реализаует рекурсивный поиск по ключу. Вернёт родителя того потомка, который с ключём.
Фильтр: один их потомков должен быть свободен.
root - корень дерева, с которого надо начать поиск.
value - значение, которое следует найти в дереве. */
Tree * Tree_Search_DisorderedDataFreeSibling(Tree * root, int value)
{
	Tree * out;
	if (root == NULL) return NULL;
	else if (root->First == NULL && root->Second == NULL) return NULL;
	else if (root->First != NULL && root->Second != NULL) /* Если у этого корня есть два потомка */
	{
		out = TSDDFS(root->First, value);
		return out == NULL ?
			TSDDFS(root->Second, value) : out;
	}
	else if (root->First != NULL) out = root->First;
	else out = root->Second;
	if (out->value == value) return root;
	else return TSDDFS(out, value);
}

#undef TSDDFS