#include "CPanel.h"
// ������ ����������
void Menu(ptrNODE& head)
{
	for (;;) {
		system("cls");
		cout << "-------------- ������ ���������� --------------" << endl;
		cout << "1. �������� ��������" << endl;
		cout << "2. ������� ��������" << endl;
		cout << "3. �������� ���������� � ��������" << endl;
		cout << "4. �������� ���������� � ���������" << endl;
		cout << "5. ���������� ��������� �� �������" << endl; // �������������� �������
		cout << "0. �����"<< endl;
		/*	����� ��������
			�.�. _getch() ���������� �������� ���� char,
			��, ����� �������� �����, ����� �� ���� ASCII ����� ������� ������� ��� ���� ('0') �� �������� ASCII.
		*/
		size_t choice = _getch() - '0'; 
		// ������� �������
		system("cls");
		/*
			� ���������� ������ �� ������� ��������� throw elements �� ������� ������.
			����� ��������� ���������� ������, ���� try-catch ��� ���������� ������ ����������.

			��� ������������ THROW, ���� CATCH ������� ���������� ������ � ��������� ������, 
			����� ���� ���������� ����� � �������� ����
		*/
		try {
			switch (choice)
			{
			case 1:
				create_student(head);
				cout << "������� ��� ������� �������� � ������!";
				Sleep(1500);
				break;
			case 2:
				delete_student(head);
				cout << "������ � �������� ���� ������� �������!";
				Sleep(1500);
				break;
			case 3:
				edit_student(head);
				cout << "������ � �������� ������� ��������!";
				Sleep(1500);
				break;
			case 4:
				print(head);
				system("pause");
				break;
			case 5:
				sort_by_marks(head);
				cout << "������ ��������� ��� ������� ������������!";
				Sleep(1500);
				break;
			case 0:
				return;
			default:
				cout << "������ ������ �� �������������!";
				break;
			}
		}
		// ��������� ������ ������
		catch (const char* ex) {
			system("cls");
			cerr << ex;
			Sleep(2000);
		}
	}

}