#include "DATA.h"

// Date

/*
Разбиение даты на переменные - день, месяц, год
*/

void Date::operator=(string date)
{
	
	// проход по всей строке "date" для последующего переноса всей даты по полям
	size_t dot = date.find(".");
	this->day = stoi(date.substr(0, dot));
	date.erase(0, dot+1);
	dot = date.find(".");
	this->month = stoi(date.substr(0, dot));
	date.erase(0, dot+1);
	this->year = stoi(date.substr(0, 4));
}

string Date::GetDate() {
	return to_string(day) + "." + to_string(month) + "." + to_string(year);
}


// Session

/*
	сессия реализована в виде словаря, созданны методы добаления, удаления и вывода информации о сессии
*/

void Session::AddSubject(string sub, int mark)
{
	if (subjects.size() == 10) throw "Добавленно максимальное количество предметов!";
	subjects[sub] = mark;
}

void Session::DeleteSubject(string sub)
{
	if(subjects.find(sub) == subjects.end()) throw "Такого предмета нет в сессии!";
	subjects.erase(sub);
}

map<string, int> Session::GetSubjects()
{
	return subjects;
}

// КОНКАТЕНАЦИЯ ПРЕДМЕТОВ ИЗ СЕМЕСТРА
string Session::GetAllSub()
{
	string str("[ ");
	
	for (auto cur : subjects) {
		str += cur.first + " " + to_string(cur.second) + " ";
	}
	str += "]";
	return str;
}

// КОНКАТЕНАЦИЯ ИНФОРМАЦИИ О СТУДЕНТЕ В СТРОКУ
string DATA::DataToString()
{
	string data;
	data = name + " " + surname + " " + patronimyc + " " + birth.GetDate() + " " +
		to_string(admision_year) + " " + faculty + " " + department + " " + group + " " +
		to_string(record_book) + " " + (sex ? "муж" : "жен") + " ";
	for (auto cur : sessions) {
		data += cur.GetAllSub() + " ";
	}

	return data;
}