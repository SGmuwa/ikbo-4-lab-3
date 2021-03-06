﻿/* Перечисление, какие команды сущесвтуют. */
enum Commands
{
	com_NaN, /* Нет такой */
	com_add, /* Добавить кружочек */
	com_show, /* Показать дерево */
	com_save, /* Сохранить состояние программы */
	com_load, /* Загрузить состояние программы */
	com_help, /* Помощь */
	com_quit, /* Выход */
	com_root, /* Обозначение узла: корневой */
	com_node, /* Узел */
	com_parent, /* Потомок */
	com_sibling, /* Ровесник */
	com_integer /* Пользователь отправил в программу число */
};