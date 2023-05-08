#pragma once
#include "DATA.h"
// ����
struct NODE
{
	DATA data;
	NODE* next;
	// ���������� ������������� ����
	NODE();
	NODE(DATA data, NODE* next = nullptr);
};
// �������� ������� ��� ���������� ��������� ���� "NODE"
using ptrNODE = NODE*;

/* ������ �� ������� �������*/

/* ������������� ������*/
void init(ptrNODE& head);

/* �������� ������ */
bool empty(ptrNODE head);

/* �������� ���������� ���� */
void add_by_pointer(ptrNODE& ptr, DATA data);
void add_head(ptrNODE& head, DATA data);
void add_after(ptrNODE& ptr, DATA data);

/* �������� �������� ���� */
void delete_by_pointer(ptrNODE& ptr);
void del_from_head(ptrNODE& head);
void del_after(ptrNODE& ptr);

/* ��������� �� ������� ������� */

// ������� ������
void clear(ptrNODE& head);
// ����� ������ � �������
void print(ptrNODE head);
// ���������� ������ �� ���������� ������ �� ���������
void sort_by_marks(ptrNODE& head);
// ������ ������ �� �����
void import(ifstream& fin, ptrNODE& head);
// ������� ������ � ����
void fexport(ofstream& out, ptrNODE& head);

/* �������� �� ������ ������������ ��������� */

// ����� �������� �� ��ר���� ������
ptrNODE& find(ptrNODE& head);
// �������� ��������
void delete_student(ptrNODE& head);
// ���������� �������� � ������
void create_student(ptrNODE& head);
// ��������� ������ ��������
void edit_student(ptrNODE& head);

/* ������� */

// ������� ������
void ParceSession(string& str, vector<Session>& sess);