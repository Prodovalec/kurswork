#include "DATA.h"

// Date

void Date::operator=(string date)
{
	
	
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

void Session::AddSubject(string sub, int mark)
{
	if (subjects.size() == 10) throw "Äîáàâëåííî ìàêñèìàëüíîå êîëè÷åñòâî ïðåäìåòîâ!";
	subjects[sub] = mark;
}

void Session::DeleteSubject(string sub)
{
	if(subjects.find(sub) == subjects.end()) throw "Òàêîãî ïðåäìåòà íåò â ñåññèè!";
	subjects.erase(sub);
}

map<string, int> Session::GetSubjects()
{
	return subjects;
}

string Session::GetAllSub()
{
	string str("[ ");
	
	for (auto cur : subjects) {
		str += cur.first + " " + to_string(cur.second) + " ";
	}
	str += "]";
	return str;
}

string DATA::DataToString()
{
	string data;
	data = name + " " + surname + " " + patronimyc + " " + birth.GetDate() + " " +
		to_string(admision_year) + " " + faculty + " " + department + " " + group + " " +
		to_string(record_book) + " " + (sex ? "ìóæ" : "æåí") + " ";
	for (auto cur : sessions) {
		data += cur.GetAllSub() + " ";
	}

	return data;
}
