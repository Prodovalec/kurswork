#pragma once
#include "DATA.h"
// УЗЕЛ
struct NODE
{
	DATA data;
	NODE* next;
	// ПЕРЕГРУЗКА КОНСТРУКТОРОВ УЗЛА
	NODE();
	NODE(DATA data, NODE* next = nullptr);
};
// СОЗДАНИЕ МАКРОСА ДЛЯ ОБЪЯВЛЕНИЯ УКАЗАТЕЛЯ ТИПА "NODE"
using ptrNODE = NODE*;

/* РАБОТА СО СВЯЗНЫМ СПИСКОМ*/

/* инициализация списка*/
void init(ptrNODE& head);

/* проверка списка */
bool empty(ptrNODE head);

/* операции добавления узла */
void add_by_pointer(ptrNODE& ptr, DATA data);
void add_head(ptrNODE& head, DATA data);
void add_after(ptrNODE& ptr, DATA data);

/* операции удаления узла */
void delete_by_pointer(ptrNODE& ptr);
void del_from_head(ptrNODE& head);
void del_after(ptrNODE& ptr);

/* операциии со связным списком */

// ОЧИСТКА СПИСКА
void clear(ptrNODE& head);
// ВЫВОД СПИСКА В КОНСОЛЬ
void print(ptrNODE head);
// СОРТИРОВКА СПИСКА ПО КОЛИЧЕСТВУ ОЦЕНОК ПО СЕМЕСТРАМ
void sort_by_marks(ptrNODE& head);
// ИМПОРТ ДАННЫХ ИЗ ФАЙЛА
void import(ifstream& fin, ptrNODE& head);
// ЭКСПОРТ ДАННЫХ В ФАЙЛ
void fexport(ofstream& out, ptrNODE& head);

/* операции со спиком относительно студентов */

// ПОИСК СТУДЕНТА ПО ЗАЧЁТНОЙ КНИЖКЕ
ptrNODE& find(ptrNODE& head);
// УДАЛЕНИЕ СТУДЕНТА
void delete_student(ptrNODE& head);
// ДОБАВЛЕНИЕ СТУДЕНТА С СПИСОК
void create_student(ptrNODE& head);
// ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА
void edit_student(ptrNODE& head);

/* ФУНКЦИИ */

// ПАРСИНГ СЕССИИ
void ParceSession(string& str, vector<Session>& sess);