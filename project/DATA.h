#pragma once
#include "modules-validators.h"

struct Date {
	int day, month, year;

	void operator= (string date);
	
	string GetDate();
};

/*	При добавлении предмета в сессию возможен такой случай, что будет передано только название предмета 
	или только оценка. Во избежание ошибки ввода была созданна структура с инкапсулированным словарём,
	который хранит в себе список сессионных предметов и их оценок.
*/
struct Session {
	// добавление словаря
	void AddSubject(string sub, int mark);
	// удаление предмета из словаря
	void DeleteSubject(string sub);
	// геттер словаря
	map<string, int> GetSubjects();
	// форматированный вывод словаря
	string GetAllSub();
private:
	// создание словаря для предметов, где ключ - название предмета, а значение - оценка
	map<string, int> subjects;
};

/* Структура DATA хранит в себе всю информацию о студенте. 
	Дата рождения и список сессий связаны со структурой DATA типом межклассовых отношений "композиция" */
struct DATA
{
	// имя, фамилия, отчество, факультет, кафедра, группа
	string name, surname, patronimyc, faculty, department, group;
	// пол
	bool sex;
	// год поступления, номер зачётной книжки
	int admision_year, record_book;
	// дата рождения
	Date birth;
	// Список сданных сессий
	vector<Session> sessions;

	string DataToString();
};