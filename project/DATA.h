#pragma once
#include "modules-validators.h"

struct Date {
	int day, month, year;

	void operator= (string date);
	
	string GetDate();
};

/*	��� ���������� �������� � ������ �������� ����� ������, ��� ����� �������� ������ �������� �������� 
	��� ������ ������. �� ��������� ������ ����� ���� �������� ��������� � ����������������� �������,
	������� ������ � ���� ������ ���������� ��������� � �� ������.
*/
struct Session {
	// ���������� �������
	void AddSubject(string sub, int mark);
	// �������� �������� �� �������
	void DeleteSubject(string sub);
	// ������ �������
	map<string, int> GetSubjects();
	// ��������������� ����� �������
	string GetAllSub();
private:
	// �������� ������� ��� ���������, ��� ���� - �������� ��������, � �������� - ������
	map<string, int> subjects;
};

/* ��������� DATA ������ � ���� ��� ���������� � ��������. 
	���� �������� � ������ ������ ������� �� ���������� DATA ����� ������������ ��������� "����������" */
struct DATA
{
	// ���, �������, ��������, ���������, �������, ������
	string name, surname, patronimyc, faculty, department, group;
	// ���
	bool sex;
	// ��� �����������, ����� �������� ������
	int admision_year, record_book;
	// ���� ��������
	Date birth;
	// ������ ������� ������
	vector<Session> sessions;

	string DataToString();
};