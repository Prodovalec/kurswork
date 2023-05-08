#include "NODE.h"

NODE::NODE()
{
	this->next = nullptr;
}

NODE::NODE(DATA data, NODE* next)
{
	this->data = data;
	this->next = next;
}

void init(ptrNODE& head)
{
	head = new NODE;
}

bool empty(ptrNODE head)
{
	return head->next == nullptr;
}

/* ОПЕРАЦИИ ДОБАВЛЕНИЯ */

void add_by_pointer(ptrNODE& ptr, DATA data)
{
	ptrNODE p = new NODE(data, ptr);
	ptr = p;
}

void add_head(ptrNODE& head, DATA data)
{
	/*ptrNODE P = new NODE(data, head);
	head = p;*/
	add_by_pointer(head, data);
}

void add_after(ptrNODE& ptr, DATA data)
{
	/*ptrNODE P = new NODE(data, ptr -> next);
	ptr -> next = p;*/
	add_by_pointer(ptr->next, data);
}

/* ОПЕРАЦИИ УДАЛЕНИЯ */

// УДАЛЕНИЕ ПО УКАЗАТЕЛЮ
void delete_by_pointer(ptrNODE& ptr)
{
	ptrNODE p = ptr;
	ptr = p->next;
	delete p;
}

// УДАЛЕНИЕ ИЗ ГОЛОВЫ СПИСКА
void del_from_head(ptrNODE& head)
{
	/*ptrNODE P = head;
	head = p -> next;
	delete p;*/
	delete_by_pointer(head);
}

// УДАЛЕНИЕ ЭЛЕМЕНТА ПОСЛЕ УКАЗАТЕЛЯ
void del_after(ptrNODE& ptr)
{
	/*ptrNODE p = ptr -> next;
	ptr -> next = p -> next;
	delete p;*/
	delete_by_pointer(ptr->next);
}

// ОЧИСТКА СПИСКА
void clear(ptrNODE& head)
{
	while (head)
		del_from_head(head);
}
/* ОПЕРАЦИИ СОС ПИСКОМ */

// ВЫВОД СПИСКА В КОНСОЛЬ
void print(ptrNODE head)
{
	if (!head) { // проверка списка
		std::cout << "Список пуст!\n";
	}
	else
	{
		std::cout << left << setw(12) << "Фамилия" << " | " << setw(10) << "Имя" << " | " << setw(12) << "Отчество" << " | ";
		std::cout << setw(10) << "Дата Рожд." << " | " << setw(15) << "Год поступления" << " | " << setw(10) << "Факультет";
		std::cout << " | "  << setw(7)<< "Кафедра" << " | " << setw(10) << "Группа" <<  " | " << setw(17) << "№ зачётной книжки" << " | " << setw(3) << "пол" << endl;
		ptrNODE p = head;
		while (p)
		{	// форматированный вывод информации о студенте
			std::cout << left << setw(12) << p->data.surname << " | " << setw(10) << p->data.name << " | " << setw(12) << p->data.patronimyc << " | ";
			std::cout << setw(10) << p->data.birth.GetDate() << " | " << setw(15) << p->data.admision_year << " | " << setw(10) << p->data.faculty;
			std::cout << " | " << setw(7) << p->data.department << " | " << setw(10) << p->data.group << " | " << setw(17) << p->data.record_book << " | " << setw(3) << (p->data.sex ? "муж" : "жен") << endl;
			// вывод всех сессий
			int c = 0;
			for (auto cur : p->data.sessions) {
				std::cout << ++c <<"-й семестр\n";
				std::cout << cur.GetAllSub() << endl;
			}
			p = p->next;
			std::cout << '\n';
		}
	}
}

// СОРТИРОВКА ОДНОСВЯЗНОГО СПИСКА ОТНОСИТЕЛЬНО КОЛИЧЕСТВА ПЯТЁРОК В ПЕРВОМ СЕМЕСТРЕ (ПО УБЫВАНИЮ)
// СОРТИРОВКА МЕТОДОМ ВСТАВКИ (INSERTION SORT)
void sort_by_marks(ptrNODE& head)
{
	if (!head) { // проверка списка
		std::cout << "Список пуст!\n";
	}
	else
	{
		auto sort_condition = [](ptrNODE node) -> size_t {
			int count = 0;
			for (auto cur : node->data.sessions[0].GetSubjects()) {
				if (cur.second == 5) count++;
			}
			return count;
		};
		if (empty(head)) return;
		ptrNODE a, b, p, h = NULL;
		for (ptrNODE i = head; i != NULL; ) {
			a = i;
			i = i->next;
			b = h;
			for (p = NULL; (b != NULL) && (sort_condition(a) < sort_condition(b)); ) {
				p = b;
				b = b->next;
			}
			if (p == NULL) {
				a->next = h;
				h = a;
			}
			else {
				a->next = b;
				p->next = a;
			}
		}
		if (h != NULL)
			head = h;
	}
}

// ИМПОРТ ДАННЫХ ИЗ ФАЙЛА В СПИСОК
void import(ifstream& fin, ptrNODE& head)
{
	init(head); // инициализация списка (очереди)
	string line;
	ptrNODE tail = head; // создание указателя на "хвост" очереди
	while (getline(fin, line))
	{
		DATA data;
		string delimiter = " ", token;
		size_t pos = 0, count = 0;
		// ПАРСИНГ ВСЕЙ СТРОКИ line
		while ((pos = line.find(delimiter)) != string::npos || pos + 1 != line.length())
		{
			token = line.substr(0, pos);
			// ИМПОРТ ВСЕЙ ИНФОРМАЦИИ В DATA ДО НАЧАЛА ПЕРЕЧИСЛЕНИЯ СЕССИЙ
			switch (count)
			{
			case 0:
				data.surname = token;
				break;
			case 1:
				data.name = token;
				break;
			case 2:
				data.patronimyc = token;
				break;
			case 3:
				data.birth = token;
				break;
			case 4:
				data.admision_year = stoi(token);
				break;
			case 5:
				data.faculty = token;
				break;
			case 6:
				data.department = token;
				break;
			case 7:
				data.group = token;
				break;
			case 8:
				data.record_book = stoi(token);
				break;
			case 9:
				data.sex = (token == "муж" ? true : false);
				break;
			default:
				break;
			}
			line.erase(0, pos + delimiter.length());
			// добавление сессий в DATA
			count++;
			if (line[0] == '[') // условие проверяющее начало перечисления сессий
			{
			ParceSession(line, data.sessions);
			}
		}
		add_after(tail, data);
		tail = tail->next;
	}
	del_from_head(head); 
}
// ЭКСПОРТ ДАННЫХ В ФАЙЛ
void fexport(ofstream& out, ptrNODE& head)
{
	ptrNODE temp = head;
	while (temp) {
		out << temp->data.DataToString() << "\n";
		temp = temp->next;
	}
}


// УДАЛЕНИЕ СТУДЕНТА
void delete_student(ptrNODE& head) {
	std::cout << "Введите номер зачётной книжки: ";
	int book = InputInt();
	if (book == 0) return;
	if (to_string(book).length() != 7)
		throw "Некорректный ввод зачётной книжки!";
	ptrNODE temp = head;
	if (temp->data.record_book == book) {
		del_from_head(head);
		return;
	}
	while (temp->next) {
		if (temp->next->data.record_book == book) {
			del_after(temp);
			return;
		}
		temp = temp->next;
	}
	throw "В списке нет студента с таким номером зачётной книжки!";
}

// ДОБАВЛЕНИЕ СТУДЕНТА С СПИСОК
void create_student(ptrNODE& head)
{
	// ПОСЛЕДОВАТЕЛЬНЫЙ ВВОД ИНФОРМАЦИИ О СТУДЕНТЕ
	DATA data;
	std::cout << "Фамилия: ";
	data.surname = InputString();
	std::cout << "Имя: ";
	data.name = InputString();
	std::cout << "Отчество: ";
	data.patronimyc = InputString();
	std::cout << "Дата Рождения: ";
	data.birth = InputDate();
	std::cout << "Год поступления: ";
	data.admision_year = InputInt();
	if (data.admision_year > 2023 || data.admision_year < 2013)
		throw "Введён неправильный год!";
	std::cout << "Факультет: ";
	data.faculty = InputString();
	std::cout << "Кафедра: ";
	data.department = InputString();
	std::cout << "Группа: ";
	data.group = InputString();
	std::cout << "Номер зачётной книжки: ";
	data.record_book = InputInt();
	if (data.record_book / 1000 != data.admision_year && to_string(data.record_book).length() != 7)
		throw "Некорректный ввод зачётной книжки!";
	std::cout << "Пол: ";
	string sex = InputString();
	(sex.find('муж') != string::npos) ?data.sex = 1: data.sex = 0;
	std::cout << "Введите количество семестров: ";
	int csess = InputInt();
	if (csess < 1 || csess > 10) throw "Некорректный ввод количества семестров!";
	// Ввод информации по всем семестрам
	for (size_t i = 0; i < csess; i++)
	{
		std::cout << i+1 << "-й Семестр\n";
		Session temp;
		try {
			while (1) {
				std::cout << "Введите название предмета: ";
				string subj = InputString();
				std::cout << "Введите оценку: ";
				int mark = InputMark();
				temp.AddSubject(subj, mark);
				std::cout << "Желаете продолжить? (Да\\Нет)";
				subj = InputString();
				if (subj == "Нет") break;
			}
		}
		catch (char* exp) {
			cerr << exp;
		}
		data.sessions.push_back(temp);
	}
	add_head(head, data);
}
// ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА
void edit_student(ptrNODE& head) {
	ptrNODE temp = find(head);
	std::cout << "Что вы хотите изменить?\n";
	std::cout << "1. Фамилию\n2. Имя\n3. Отчество\n4. Дату Рождения\n5. Год поступления\n6. Факультет";
	std::cout << "\n7. Номер зачётной книжки\n8. Информацию по сессии\n0. Выход\n";
	size_t choice = _getch() - '0';
	switch (choice)
	{
	case 1:
		temp->data.surname = InputString();
		break;
	case 2:
		temp->data.name = InputString();
		break;
	case 3:
		temp->data.patronimyc = InputString();
		break;
	case 4:
		temp->data.birth = InputDate();
		break;
	case 5:
		temp->data.admision_year = InputInt();
		if (temp->data.admision_year > 2023 || temp->data.admision_year < 2013) throw "Введён неправильный год!";
		break;
	case 6:
		temp->data.faculty = InputString();
		temp->data.department = InputString();
		temp->data.group = InputString();
		break;
	case 7:
		temp->data.record_book = InputInt();
		if (temp->data.record_book / 1000 != temp->data.admision_year && to_string(temp->data.record_book).length() != 7)
			throw "Некорректный ввод зачётной книжки!";
		break;
	case 8:
	{
		std::cout << "Введите номер семестра: ";
		int sem = InputInt();
		if (sem < 0 || sem > temp->data.sessions.size()) throw "Неправильный ввод номера семестра!";
		std::cout << "Введите название предмета: ";
		string subj = InputString();
		map<string, int> ::iterator it = temp->data.sessions[sem].GetSubjects().find(subj);
		if (it == temp->data.sessions[sem].GetSubjects().end()) {
			throw "Такого предмета нет в данной сессии!";
		}
		else {
			std::cout << "Изменение предмета с " << it->first << " на: ";
			it->second = InputMark();
		}
	}
		break;
	default:
		std::cout << "Такого выбора не предусмотренно!";
		break;
	}
}
// ПОИСК СТУДЕНТА ПО ЗАЧЁТНОЙ КНИЖКЕ
ptrNODE& find(ptrNODE& head)
{
	std::cout << "Введите номер зачётной книжки: ";
	int book = InputInt();
	if (to_string(book).length() != 7)
		throw "Некорректный ввод зачётной книжки!";
	ptrNODE temp = head;
	while (temp)
	{
		if (temp->data.record_book == book)
			return temp;
		temp = temp->next;
	}
	throw "В списке нет студента с таким номером зачётной книжки!";
}
// ПАРСИНГ СЕССИИ (СТРОКИ)
void ParceSession(string& str, vector<Session>& sess)
{
	size_t csubj = 0, pos;
	while (str.size() > 0) {
		if (str[0] == '\r') {
			str.clear();
			break;
		}
		str.erase(0, 2); // удаление "["
		Session temp; // создание объекта для ввода информации о сессиях
		// парсинг блока с сессиями, обособленных "[]"
		while (((pos = str.find_first_of("12345")) != string::npos) && str[0] != '[') {
			temp.AddSubject(str.substr(0, pos - 1), str[pos] - '0');
			// удлаение обраотанной части строки
			str[pos + 2] == ']' ? str.erase(0, pos + 4) : str.erase(0, pos + 2);
		}
		sess.push_back(temp);
	}
}