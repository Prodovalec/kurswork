#include "CPanel.h"
// Панель Управления
void Menu(ptrNODE& head)
{
	for (;;) {
		system("cls");
		cout << "-------------- Панель Управления --------------" << endl;
		cout << "1. Добавить студента" << endl;
		cout << "2. Удалить студента" << endl;
		cout << "3. Изменить информацию о студенте" << endl;
		cout << "4. Просмотр информации о студентах" << endl;
		cout << "5. Сортировка студентов по оценкам" << endl; // индивидуальное задание
		cout << "0. Выход"<< endl;
		/*	Выбор действия
			Т.к. _getch() возвращает значение типа char,
			то, чтобы получить число, нужно из кода ASCII этого символа вычесть код нуля ('0') из такблицы ASCII.
		*/
		size_t choice = _getch() - '0'; 
		// ОЧИСТКА КОНСОЛИ
		system("cls");
		/*
			В процедурах работы со списком прописаны throw elements со строкой ошибки.
			Чтобы программа продолжала работу, блок try-catch был расположен Панели управления.

			ПРИ СРАБАТЫВАНИИ THROW, БЛОК CATCH ВЫВЕДЕТ ПЕРЕДАННУЮ СТРОКУ С ОПИСАНИЕМ ОШИБКИ, 
			ПОСЛЕ ЧЕГО ВЫПОЛНИТСЯ ВЫХОД В ОСНОВНОЕ МЕНЮ
		*/
		try {
			switch (choice)
			{
			case 1:
				create_student(head);
				cout << "Студент был успешно добавлен в список!";
				Sleep(1500);
				break;
			case 2:
				delete_student(head);
				cout << "Данные о студенте были успешно удалены!";
				Sleep(1500);
				break;
			case 3:
				edit_student(head);
				cout << "Данные о студенте успешно изменены!";
				Sleep(1500);
				break;
			case 4:
				print(head);
				system("pause");
				break;
			case 5:
				sort_by_marks(head);
				cout << "Список студентов был успешно отсортирован!";
				Sleep(1500);
				break;
			case 0:
				return;
			default:
				cout << "Такого выбора не предусмотрено!";
				break;
			}
		}
		// ОБРАБОТКА СТРОКИ ОШИБКИ
		catch (const char* ex) {
			system("cls");
			cerr << ex;
			Sleep(2000);
		}
	}

}