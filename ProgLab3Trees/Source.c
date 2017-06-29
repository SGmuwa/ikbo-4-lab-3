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
	count = 0u;
	return strcpy(to, from) == to ? 0 : EACCES;
#else
	return strcpy_s(to, (rsize_t)count, from);
#endif
}

#include "GetCommands.h"
#include "Tree.h"

/*
������� ������:
add root 2
add node 10 parent root
add node 3 parent root
add node 12 parent 3
add node 4 sibling 12

add root 1 add node 2 parent root add node 3 parent 1 add node 4 parent 2 add node 5 sibling 4
*/

void run(void)
{
#define GETCOM (comv = GetCommand())
	struct commands_value comv = { com_NaN, 0 };
	int arg[2] = { 0 }; /* ��������� ���������, ������� ������� ������������. */
	Tree * Object = NULL; /* ������� ������. */
	Tree * sch = NULL; /* ���� ������������ ��������� ������. */
	Tree ** ControlBranches = NULL; /* ������� ��� ����������� � ������� ��������. */
	enum FLAG
	{
		NaN = com_NaN,
		parent = com_parent, /* ������� */
		sibling = com_sibling, /* ��������� */
		root = com_root, /* ������ */
		node = com_node /* ����*/
	} fAdd = NaN, /* ���� ����������, ����� ������� ��������. */
		newObject = NaN; /* ��� ���� ��������? */
	while (1u)
	{
		Tree_Print(Object, stdout);
		Tree_PrintStatistics(Object, stdout);
		switch (GETCOM.c)
		{
		case com_add: /* add */
			if (GETCOM.c != com_root && comv.c != com_node) break;
			newObject = (enum FLAG)comv.c; /* add root|node */
			if (GETCOM.c != com_integer) break;
			arg[0] = comv.v; /* add root|node %d*/
			if (newObject == root) /* add root %d */
			{
				Tree_Free(Object);
				Object = Tree_Malloc(arg[0]);
				break;
			} /* else if newObject == com_node */
			/* add node %d */
			fAdd = (enum FLAG)GETCOM.c;
			if (fAdd != parent && fAdd != sibling) break;
			/* add node %d patern|sibling*/
			if (GETCOM.c != com_integer && comv.c != com_root) break;
			/* � ������, ���� ��������� �������� � ���������, �� �� � ��������� ������ ���������� �������� �����. */
			if (comv.c == com_root && Object == NULL) break;
			arg[1] = comv.c == com_root ? Object->value : comv.v;
			/* add node %d patern|sibling %d|root */
			if (fAdd == sibling)
			{
				/* add node %d sibling %d */
				if (comv.c == com_root) break;
				sch = Tree_Search_DisorderedDataFreeSibling(Object, arg[1]);
				if (sch == NULL)
				{
					printf("not found.\n");
					break;
				}
				ControlBranches = sch->First == NULL ? &sch->First : &sch->Second;
				*ControlBranches = Tree_Malloc(arg[0]);
			}
			else /*if (fAdd == parent)*/
			{
				/* add node %d patern %d|root */
				sch = Tree_Search_DisorderedDataFreeParent(Object, arg[1]);
				if (comv.c == com_root && sch != Object)
				{
					printf("error add to root.\n");
					break;
				}
				if (sch == NULL)
				{
					printf("not found.\n");
					break;
				}
				ControlBranches = sch->First == NULL ? &sch->First : &sch->Second;
				*ControlBranches = Tree_Malloc(arg[0]);
				break;
			}
			break;
		case com_quit:
			return;
		default:
			break;
		}
	}
#undef GETCOM
}

void main(void)
{
	run();
	return;
}

#undef iMAX_CH
