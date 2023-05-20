#pragma once // гарантия, что хедер будет включен только один раз в программу
// подключение всех необходимых библиотек
#include <iostream>		// console input/output
#include <Windows.h>	// для работы Sleep & установки кодировки консоли
#include <fstream>		// file input/output (работа с файлами)
#include <string>		// string (строки)
#include <vector>		// работа с вектором (контейнер)
#include <map>			// работа со словарём (контейнер)
#include <regex>		// регулярные выражения (валидация даты рождения)
#include <conio.h>		// _getch() (функция для моментального считывания введённого символа через консоль без нажатия enter)
#include <iomanip>		// форматирование вывод в консоль

using namespace std;

int InputInt();
unsigned short InputMark(); // оценки
string InputString();
string InputDate();

// ВАЛИДИРОВАННЫЙ ВВОД ЦЕЛОГО ЧИСЛА
int InputInt()
{
    int num;
    while (1) { // бесконечный цикл, пока не будет выполнено условие (корректное число)
        cin >> num;
        /*
            fail() возвращает бит ошибки, при некорректном вводе(буква или др.)
            будет очищен поток cin, а также вывод в консоль о неправильном вводе
        */
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Некорректный ввод числа!\nПопробуйте ещё раз:";
            continue;
        }
        return num;
    }
}
// ВАЛИДИРОВАННЫЙ ВВОД ОЦЕНКИ (if < 1 - comeback 1, if > 5 - comeback 5)
unsigned short InputMark()
{
    short mark;
    while (1) { // бесконечный цикл, пока не будет выполнено условие (ввод оценки от 1 до 5 включительно)
        mark = InputInt(); // ввод оценки
        if (mark < 1) mark = 1;
        else if (mark > 5) mark = 5;
        return mark;
    }
}

// ВАЛИДИРОВАННЫЙ ВВОД СТРОКИ
string InputString()
{
    // ВВОД СТРОКИ, УЧИТЫВАЯ ПРОБЕЛЫ КАК СИМВОЛ, А НЕ КОНЕЦ СТРОКИ (ws - whitespace)
    string str;
    getline(cin >> ws, str); // чтение строки ввода cin и сохранение её в переменную str 
    return str;
}

// ВАЛИДИРОВАННЫЙ ВВОД ДАТЫ РОЖДЕНИЯ
string InputDate()
{
    /* Валидация даты рождения. Если введённая дата не будет соответствовать данному шаблону (ДД.ММ.ГГГГ, где ДД - 01 ДО 31, ММ - ОТ 01 ДО 12. ГГГГ - ОТ 1993 ДО 2004),
       то будет дано сообщение о некорректности ввода даты
       Первый символ для дня, может быть 2-х значным от 01 до 31 (разрешён ввод 1 цифры от 0 до 9)
       Второй символ для месяца, может быть 2-х значным от 01 до 12 (разрешён ввод 1 цифры от 0 до 9)
       Третий символ для года, может быть 4-х значным числом от 1993 до 2004)
       regex - класс, для работы с регулярными выражениями - это шаблоны, которые удовлетворяют определённые правила)
       */
       //                  day             month           year
    regex reg("([0-2][0-9]|3[0-1]|[0-9]).(0[0-9]|1[0-2]|[0-9]).(199[3-9]|200[0-4])");

    string date = InputString();
    if (!regex_match(date, reg)) throw "Некорректно введена дата рождения!"; //regex_match - проверка date по шаблону, if соответствует - comeback true, else - false
    return date;
}

struct Date {
    int day, month, year;

    void operator= (string date); // перегружает оператор =(присваивания) для объекта Date

    string GetDate(); // возврат даты в виде строки
};

/* Структура Date перегружает оператор присваивания для преобразования строки в объект 'Date'
При добавлении предмета в сессию возможен такой случай, что будет передано только название предмета
    или только оценка. Во избежание ошибки ввода была создана структура с инкапсулированным словарём,
    который хранит в себе список сессионных предметов и их оценок.
*/
struct Session { // описывает сессию и хранит в себе словарь, где ключ - название предмета, а значение - оценка
    // добавление словаря
    void AddSubject(string sub, int mark);
    // удаление предмета из словаря
    void DeleteSubject(string sub);
    // геттер словаря (возвращает словарь с названиями предметов и их оценками)
    map<string, int>& GetSubjects();
    // форматированный вывод словаря
    string GetAllSub();
private:
    // создание словаря для предметов, где ключ - название предмета, а значение - оценка
    map<string, int> subjects;
};  // map (контейнер, хранящий данные и позволяющий быстро находить значения по ключу)

/* Класс DATA хранит в себе всю информацию о студенте.
    Дата рождения и список сессий связаны с классом DATA типом межклассовых отношений (класс DATA содержит в себе объекты других классов, в данном случае структуру Date и класс Session) "композиция"
    (композиция позволяет создавать более сложные объекты, объединяя их из более простых компонентов */
class DATA
{
public:
    // имя, фамилия, отчество, факультет, кафедра, группа
    string name, surname, patronimyc, faculty, department, group;
    // пол
    bool sex; // bool может принимать только 2 значения: true or false
    // год поступления, номер зачётной книжки
    int admision_year, record_book;
    // дата рождения
    Date birth; // объявление Date с именем birth => в структуре DATA переменная birth будет хранить info about birthday(dd.mm.yyyy)
    // Список сданных сессий
    vector<Session> sessions; // vector (класс), позволяет создавать массивы и изменять их размер, если заполняется, то автоматически увеличивается сам

    string DataToString(); // преобразует данные студента в строку для вывода.
};

// Односвязной список, содержащий узлы NODE, каждый из которых хранит объект типа DATA и указатель на следующий узел списка
NODE::NODE() // конструктор, который инициализирует указатель класса NODE значением nullptr
{
	this->next = nullptr; // указатель на нулевой адрес памяти (если не нужно указывать на что-то конкретное))
}

/* ИНИЦИАЛИЗАЦИЯ ПОЛЯ DATA AND NEXT КЛАССА NODE ПЕРЕДАННЫМИ ЗНАЧЕНИЯМИ */
NODE::NODE(DATA data, NODE* next) // реализация конструктора для узла списка NODE
{
	this->data = data; // присваивает полю data переданный объект data
	this->next = next; // присваивает указатель next на следующий узел списка
}

/* ИНИЦИАЛИЗАЦИЯ УКАЗАТЕЛЯ head ПРИ СОЗДАНИИ НОВОГО УЗЛА С ПОМОЩЬЮ new (выделение динамической памяти) */
void init(ptrNODE& head)
{
	head = new NODE;
}

/* ПРОВЕРКА НА ПУСТОТУ СПИСКА (есть ли у главного узла указатель на следующий узел) */
bool empty(ptrNODE head)
{
	return head->next == nullptr;
}

/* ОПЕРАЦИИ ДОБАВЛЕНИЯ */

void add_by_pointer(ptrNODE& ptr, DATA data) // указатель ptr заменяется на новый узел, созданный с помощью оператора new
{
	ptrNODE p = new NODE(data, ptr); // создание узла p,  
	ptr = p;
}

void add_head(ptrNODE& head, DATA data) // добавляет новый узел в начало списка
{
	/*ptrNODE P = new NODE(data, head);
	head = p;*/
	add_by_pointer(head, data);
}

void add_after(ptrNODE& ptr, DATA data) // добавление нового узла со значением data, после узла ptr, который не должен быть последним в списке
{
	/*ptrNODE P = new NODE(data, ptr -> next);
	ptr -> next = p;*/
	add_by_pointer(ptr->next, data);
}

/* ОПЕРАЦИИ УДАЛЕНИЯ */

// УДАЛЕНИЕ ПО УКАЗАТЕЛЮ
void delete_by_pointer(ptrNODE& ptr) // удаляет узел, на который указывает переданный указатель, затем перенаправляет указатель на следующий узел
{
	ptrNODE p = ptr;
	ptr = p->next;
	delete p;
}

// УДАЛЕНИЕ ИЗ ГОЛОВЫ СПИСКА
void del_from_head(ptrNODE& head) // удаляет первый узел в списке
{
	/*ptrNODE P = head;
	head = p -> next;
	delete p;*/
	delete_by_pointer(head);
}

// УДАЛЕНИЕ ЭЛЕМЕНТА ПОСЛЕ УКАЗАТЕЛЯ
void del_after(ptrNODE& ptr) // удаляет узел после узла, на который указывает переданный указатель
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
		del_from_head(head); // удаляет элементы из головы списка, пока список не станет пустым
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
		std::cout << "Выберите опцию:\n";
		std::cout << "1. Вывести студентов мужского пола\n";
		std::cout << "2. Вывести студентов женского пола\n";
		std::cout << "3. Вывести всех студентов\n";
		/*	Выбор действия
			Т.к. _getch() возвращает значение типа char,
			то, чтобы получить число, нужно из кода ASCII этого символа вычесть код нуля ('0') из таблицы ASCII.
		*/
		size_t choice = _getch() - '0';
		system("cls");
		ptrNODE p = head; // создание указателя p, который указывает на тот узел, на который указывает указатель head
		while (p)
		{	// форматированный вывод информации о студенте
			if (choice == 1 && p->data.sex == true) {
				std::cout << left << setw(12) << p->data.surname << " | " << setw(10) << p->data.name << " | " << setw(15) << p->data.patronimyc << " | ";
				std::cout << setw(13) << p->data.birth.GetDate() << " | " << setw(15) << p->data.admision_year << " | " << setw(10) << p->data.faculty;
				std::cout << " | " << setw(7) << p->data.department << " | " << setw(10) << p->data.group << " | " << setw(17) << p->data.record_book << " | " << setw(3) << "муж" << endl;
				// вывод всех сессий
				int c = 0;
				for (auto cur : p->data.sessions) { // auto - автоматическое определение типа для cur на основе элементов в sessions, который находится в объекте p->data => будет иметь тип элементов в контейнере sessions
					std::cout << ++c << "-й семестр\n";
					std::cout << cur.GetAllSub() << endl; // возврат строки с информацией о всех предметах
				}
				std::cout << '\n';
			}
			else if (choice == 2 && p->data.sex == false) { // выводим только женщин
				std::cout << left << setw(12) << p->data.surname << " | " << setw(10) << p->data.name << " | " << setw(15) << p->data.patronimyc << " | ";
				std::cout << setw(13) << p->data.birth.GetDate() << " | " << setw(15) << p->data.admision_year << " | " << setw(10) << p->data.faculty;
				std::cout << " | " << setw(7) << p->data.department << " | " << setw(10) << p->data.group << " | " << setw(17) << p->data.record_book << " | " << setw(3) << "жен" << endl;
				// вывод всех сессий
				int c = 0;
				for (auto cur : p->data.sessions) { // auto - автоматическое определение типа для cur на основе элементов в sessions, который находится в объекте p->data => будет иметь тип элементов в контейнере sessions
					std::cout << ++c << "-й семестр\n";
					std::cout << cur.GetAllSub() << endl; // возврат строки с информацией о всех предметах
				}
				std::cout << '\n';
			}
			else if (choice == 3) { // выводим всех студентов
				std::cout << left << setw(12) << p->data.surname << " | " << setw(10) << p->data.name << " | " << setw(15) << p->data.patronimyc << " | ";
				std::cout << setw(13) << p->data.birth.GetDate() << " | " << setw(15) << p->data.admision_year << " | " << setw(10) << p->data.faculty;
				std::cout << " | " << setw(7) << p->data.department << " | " << setw(10) << p->data.group << " | " << setw(17) << p->data.record_book << " | ";
				if (p->data.sex) {
					std::cout << setw(3) << "муж";
				}
				else {
					std::cout << setw(3) << "жен";
				}
				std::cout << endl;
				// вывод всех сессий
				int c = 0;
				for (auto cur : p->data.sessions) { // auto - автоматическое определение типа для cur на основе элементов в sessions, который находится в объекте p->data => будет иметь тип элементов в контейнере sessions
					std::cout << ++c << "-й семестр\n";
					std::cout << cur.GetAllSub() << endl; // возврат строки с информацией о всех предметах
				}
				std::cout << '\n';
			}
			p = p->next; // перенос указателя p на следующий узел в списке, нужно для прохода по всем узлам в списке и вывода информации о каждом студенте и его сессиях
		}
	}
}

// СОРТИРОВКА ОДНОСВЯЗНОГО СПИСКА ОТНОСИТЕЛЬНО КОЛИЧЕСТВА ПЯТЁРОК В ПЕРВОМ СЕМЕСТРЕ (ПО УБЫВАНИЮ)
// СОРТИРОВКА МЕТОДОМ ВСТАВКИ (INSERTION SORT - проходит по списку элементов и вставляет каждый элемент на своё место в уже отсортированную часть списка)
void sort_by_marks(ptrNODE& head)
{
	if (!head) { // проверка списка
		std::cout << "Список пуст!\n";
	}
	else
	{
		auto sort_condition = [](ptrNODE node) -> size_t { // определяет количество пятерок в первом семестре каждого узла списка, затем сортирует список, перемещая узлы в нужное место
			int count = 0;
			for (auto cur : node->data.sessions[0].GetSubjects()) {
				if (cur.second == 5) count++;
			}
			return count;
		};
		if (empty(head)) return;
		ptrNODE a, b, p, h = NULL; // создание 3-х указателей (a b p) на узлы и 1 (h) на головной узел
		for (ptrNODE i = head; i != NULL; ) { // цикл проходится по всем узлам списка i, переназначая переменные (a i b)
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

// ИМПОРТ ДАННЫХ ИЗ ФАЙЛА В СПИСОК C ПОМОЩЬЮ add_after
void import(ifstream& fin, ptrNODE& head)
{
	init(head); // инициализация списка (очереди)
	string line;
	ptrNODE tail = head; // создание указателя на "хвост" очереди
	while (getline(fin, line)) // считывает строки из файла по одной строке за раз, пока не дойдёт до конца, каждая строка сохраняется в переменной line
	{
		DATA data;
		string delimiter = " ", token; // инициализация delmiter пробелом, token используется для хранения отдельных токенов из строки line
		size_t pos = 0, count = 0; // size_t (беззнаковое целое число) присваивает pos and count значения 0
		// ПАРСИНГ ВСЕЙ СТРОКИ line
		while ((pos = line.find(delimiter)) != string::npos || pos + 1 != line.length()) // разбивает каждую строку файла на токены и затем парсит их, чтобы заполнить структуру DATA
		{
			token = line.substr(0, pos); // создаёт новую строку token, которая содержит подстроку line, начиная с индекс 0 до pos-1
			// ИМПОРТ ВСЕЙ ИНФОРМАЦИИ В DATA ДО НАЧАЛА ПЕРЕЧИСЛЕНИЯ СЕССИЙ
			switch (count) // выбор какой case выбрать
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
			line.erase(0, pos + delimiter.length()); // удаление обработанного токена и разделителя из строки line для обработки следующего токена
			// добавление сессий в DATA
			count++; // увеличение значения переменной count на 1 и используется для отслеживания порядкового номера токена в строке line
			if (line[0] == '[') // условие проверяющее начало перечисления сессий
			{
				ParceSession(line, data.sessions); // обнаруживает начало перечисления сессий, она вызывает функцию ParceSession для добавления сессий в структуру DATA
			}
		}
		add_after(tail, data); // добавляет узел списка, содержащий эту структуру, в конец списка
		tail = tail->next; // обновление указателя tail на следующий элемент списка
	}
	del_from_head(head); // удаляет заголовочный элемент, чтобы вернуть список без него
}
// ЭКСПОРТ ДАННЫХ В ФАЙЛ ИЗ СПИСКА
void fexport(ofstream& out, ptrNODE& head) // ofstream - представляет собой выходной поток для записи в файл
{
	ptrNODE temp = head;                           // fexport - перебирает все узлы списка и записывает информацию о каждом студенте в файл
	while (temp) {
		out << temp->data.DataToString() << "\n"; // DataToString() для преобразования информации о студенте в строку
		temp = temp->next; // объявление указателя temp на следующий элемент списка
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
	if (temp->data.record_book == book) { // сравнение номера зачётной книжки студента, хранящегося в текущем узле списка
		del_from_head(head); // если узел в начале списка
		return;
	}
	while (temp->next) { // цикл, пока temp указывает на узел, который имеет следующий узел в списке
		if (temp->next->data.record_book == book) { // проверка на соответствие номера зачётной книжки следующего узла в списке искомому значению book
			del_after(temp); // если узел в середине списка
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
	if (data.record_book / 1000 != data.admision_year && to_string(data.record_book).length() != 7) // проверка на корректность ввода номера зачётной книжки
		throw "Некорректный ввод зачётной книжки!";
	std::cout << "Пол: ";
	string sex_str = InputString();
	if (sex_str == "муж") {
		data.sex = 1;
	}
	else if (sex_str == "жен") {
		data.sex = 0;
	}
	else {
	}
	std::cout << "Введите количество семестров: ";
	int csess = InputInt();
	if (csess < 1 || csess > 10) throw "Некорректный ввод количества семестров!"; // проверка вводимого кол-ва семестров
	// Ввод информации по всем семестрам
	for (size_t i = 0; i < csess; i++)
	{
		std::cout << i + 1 << "-й Семестр\n";
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
		catch (char* exp) { // выполняется в случае вызова исключения char в блоке try
			cerr << exp; // вывод сообщения об ошибке
		}
		data.sessions.push_back(temp);
	}
	add_head(head, data); // добавление узла в начало списка
}
// ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА

void edit_student(ptrNODE& head) {
	ptrNODE temp = find(head); // возвращение указателя на узел, который присваивается переменной temp
	std::cout << "Что вы хотите изменить?\n";
	std::cout << "1. Фамилию\n2. Имя\n3. Отчество\n4. Дату Рождения\n5. Год поступления\n6. Факультет\n7. Кафедру\n8. Группу";
	std::cout << "\n9. Номер зачётной книжки\n10. Пол\n11. Информацию о сессии студента\n0. Выход\n";
	size_t choice = InputInt();
	switch (choice)
	{
	case 1:
		std::cout << "Введите новую фамилию: ";
		std::cin.ignore();
		temp->data.surname = InputString();
		break;
	case 2:
		std::cout << "Введите новое имя: ";
		std::cin.ignore();
		temp->data.name = InputString();
		break;
	case 3:
		std::cout << "Введите новое отчество: ";
		std::cin.ignore();
		temp->data.patronimyc = InputString();
		break;
	case 4:
		std::cout << "Введите новую дату рождения: ";
		std::cin.ignore();
		temp->data.birth = InputDate();
		break;
	case 5:
		std::cout << "Введите новый год поступления: ";
		std::cin.ignore();
		temp->data.admision_year = InputInt();
		if (temp->data.admision_year > 2023 || temp->data.admision_year < 2013) throw "Введён неправильный год!";
		break;
	case 6:
		std::cout << "Введите новый факультет: ";
		std::cin.ignore();
		temp->data.faculty = InputString();
		break;
	case 7:
		std::cout << "Введите новую кафедру: ";
		std::cin.ignore();
		temp->data.department = InputString();
		break;
	case 8:
		std::cout << "Введите новую группу: ";
		std::cin.ignore();
		temp->data.group = InputString();
		break;
	case 9:
		std::cout << "Введите новый номер зачётной книжки: ";
		std::cin.ignore();
		temp->data.record_book = InputInt();
		if (temp->data.record_book / 1000 != temp->data.admision_year && to_string(temp->data.record_book).length() != 7)
			throw "Некорректный ввод зачётной книжки!";
		break;
	case 10:
		std::cout << "Введите новый пол (1 - муж, 0 - жен): ";
		std::cin.ignore();
		temp->data.sex = InputInt();
		break;
	case 11:
	{
		std::cout << "Введите номер семестра: ";
		int sem = InputInt();
		if (sem < 0 || sem > temp->data.sessions.size()) throw "Неправильный ввод номера семестра!"; // проверка номера семестра, если значение < 0, либо > кол-ва семестров, сохранённых в векторе
		std::cout << "Введите название предмета: ";
		string subj = InputString();
		map<string, int> ::iterator it = temp->data.sessions[sem - 1].GetSubjects().find(subj); // ищет элемент с ключом subj в данном контейнере и
		if (it == temp->data.sessions[sem - 1].GetSubjects().end()) {                           // возвращает итератор на найденный элемент (или итератор на конец контейнера, если элемент не найден)
			throw "Такого предмета нет в данной сессии!";
		}
		else {
			std::cout << "Изменение оценки по предмету " << it->first << " с " << it->second << " на: ";
			it->second = InputMark();
		}
	}
	break;
	default:
		std::cout << "Такого выбора не предусмотрено!";
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
	while (temp) // цикл будет продолжаться до тех пор, пока указатель temp не станет нулевым (не будет указывать на конец списка)
	{
		if (temp->data.record_book == book) // проверяет, совпадает ли значение номера зачётной книжки студента с заданным значением book
			return temp;
		temp = temp->next;
	}
	throw "В списке нет студента с таким номером зачётной книжки!";
}
// ПАРСИНГ СЕССИИ (СТРОКИ)
void ParceSession(string& str, vector<Session>& sess) // парсит информацию о сессиях студента из строки и записывает её в вектор сессий
{
	size_t csubj = 0, pos;
	while (str.size() > 0) {    // происходит поиск символа "[" для определения начала блока сессии, пока не найден символ "]" (конец блока) => 
		if (str[0] == '\r') {   // => из строки извлекается информация о каждом предмете и его оценке которые затем записываются в объект сессии
			str.clear();
			break;
		}
		str.erase(0, 2); // удаление "["
		Session temp; // создание объекта для ввода информации о сессиях
		// парсинг блока с сессиями, обособленных "[]"
		while (((pos = str.find_first_of("12345")) != string::npos) && str[0] != '[') {  // выполняется до тех пор, пока в строке str не будет найден символ [ или пока не будет достигнут конец строки (string::npos)
			temp.AddSubject(str.substr(0, pos - 1), str[pos] - '0');
			// удаление обработанной части строки
			str[pos + 2] == ']' ? str.erase(0, pos + 4) : str.erase(0, pos + 2); // Если в позиции pos+2 в строке находится символ ']' =>
			// => то удаляются 4 символа: символ ']', пробел, символ '\n', и символ '\r' (символы конца блока сессии)
			// в противном случае удаляются только 2 символа: пробел и символ '\n' (символы, разделяющие предметы внутри блока сессии).
		}
		sess.push_back(temp); // добавление temp в конец вектора sess
	}
}

// Date - реализация классов Date and Session, а также Data

/*
Разбиение даты на переменные - день, месяц, год
*/

void Date::operator=(string date) // принимает на вход строку, содержащую дату в формате "ДД.ММ.ГГГГ", и разбивает ее на отдельные компоненты даты - день, месяц и год
{

	// проход по всей строке "date" для последующего переноса всей даты по полям
	size_t dot = date.find("."); // находит первую позицию символа в строке date и сохраняет в переменную dot.
	this->day = stoi(date.substr(0, dot)); // разбивает date на отдельные компоненты (дата, месяц, год)
	date.erase(0, dot + 1); // удаление из строки date все символы с 0 позиции до точки и увеличение его позиции на 1
	dot = date.find("."); // нахождение первой позиции точки в строке date, затем позиция сохраняется в переменную dot
	this->month = stoi(date.substr(0, dot)); // извлечение из строки date подстроки, начиная с 0-го индекса и до позиции точки, преобразует её в целое число с помощью stoi, после присваивает значение полю month
	date.erase(0, dot + 1);
	this->year = stoi(date.substr(0, 4)); // извлечение первых 4-х символов из строки date with функции substr(), начиная с 1-го символа(0), преобразовывая их в int значение с помощью stoi()
}

string Date::GetDate() {
	return to_string(day) + "." + to_string(month) + "." + to_string(year); // возвращает дату в формате (ДД.ММ.ГГГГ), объединяя значения полей дня, месяца и года
}

// Session

/*
	сессия реализована в виде словаря, созданы методы добавления, удаления и вывода информации о сессии
*/

void Session::AddSubject(string sub, int mark) // определение метода класса session с именем AddSbject, который принимает 2 параметра: sub & mark
{
	if (subjects.size() == 10) throw "Добавлено максимальное количество предметов!"; // если кол-во предметов достигло 10, выбрасывает исключение
	subjects[sub] = mark; // присваивание оценки mark предмету с названием sub
}

void Session::DeleteSubject(string sub) // удаление предмета из сессии студента, sub - название предмета, который нужно удалить
{
	if (subjects.find(sub) == subjects.end()) throw "Такого предмета нет в сессии!"; // если элемент не найден, то вызывается исключение
	subjects.erase(sub); // удаление элемента sub из subject
}

map<string, int>& Session::GetSubjects() // возвращает словарь предметов с оценками
{
	return subjects;
}

// КОНКАТЕНАЦИЯ (объединение двух или более строк в одну строку(объединение информации о студенте и его сессиях в одну строку при вызове метода DataToString() класса DATA) ПРЕДМЕТОВ ИЗ СЕМЕСТРА
string Session::GetAllSub() // возвращает строку, содержащую конкатенацию всех предметов в сессии в формате "[ название_предмета оценка ... ]"
{
	string str("[ "); // инициализация переменной str строкой [

	for (auto cur : subjects) { // автоматические определение типа переменной cur, где =>
		str += cur.first + " " + to_string(cur.second) + " "; // => cur.first - название предмета, а cur.second - оценка
	}
	str += "]"; // добавление символа ]
	return str;
}

// КОНКАТЕНАЦИЯ ИНФОРМАЦИИ О СТУДЕНТЕ В СТРОКУ
string DATA::DataToString() // возвращает строку, содержащую все данные объекта класса DATA, формируется путем конкатенации всех полей объекта класса DATA, включая словарь сессий, который конвертируется в строку при помощи метода GetAllSub.
{
	string data;
	data = surname + " " + name + " " + patronimyc + " " + birth.GetDate() + " " +        // формирование начальной строки, которая содержит данные студента
		to_string(admision_year) + " " + faculty + " " + department + " " + group + " " +
		to_string(record_book) + " " + (sex ? "муж" : "жен") + " ";
	for (auto cur : sessions) { // цикл проходится по каждой сессии в словаре session и добавляет результат GetAllSub =>
		data += cur.GetAllSub() + " "; // => который возвращает строку, содержащую все предметы с оценками в текущей сессии
	}

	return data; // содержит информацию обо всех сессиях студента, хранящуюся в DATA в виде строки
}
// УЗЕЛ (Связной список - структура данных, состоящая из узлов, где каждый узел содержит данные и ссылку на следующий узел в списке.)
struct NODE
{
	DATA data; // объявление переменной data типа DATA
	NODE* next; // объявление указателя на следующий узел списка
	// ПЕРЕГРУЗКА КОНСТРУКТОРОВ УЗЛА
	NODE(); // объявление конструктора для структуры NODE
	NODE(DATA data, NODE* next = nullptr); // перегрузка конструктора класса NODE, при создании нового узла происходит инициализация полей data and next
};  // Если указатель не передан на следующий узел, то он инициализуется nullptr (указатель не указывает ни на какой объект)

// СОЗДАНИЕ МАКРОСА ДЛЯ ОБЪЯВЛЕНИЯ УКАЗАТЕЛЯ ТИПА "NODE" для удобства работы с указателями на узлы списка (Макрос используется для упрощения объявления переменных, функций и параметров, относящихся к указателям на структуру NODE)
using ptrNODE = NODE*;

/* РАБОТА СО СВЯЗНЫМ СПИСКОМ*/

/* инициализация списка*/
void init(ptrNODE& head);

/* проверка на пустоту списка */
bool empty(ptrNODE head); // проверяет, является ли указатель на голову списка head пустым. Если он nullptr возвращает true, если не равно nullptr, то возвращает false 

/* операции добавления узла */
void add_by_pointer(ptrNODE& ptr, DATA data); // добавляет новый узел после указанного узла, на который указывает ptr
void add_head(ptrNODE& head, DATA data); // добавляет новый узел в начало списка
void add_after(ptrNODE& ptr, DATA data); // добавляет новый узел между текущим узлом, на который указывает ptr и следующим узлом

/* операции удаления узла */
void delete_by_pointer(ptrNODE& ptr); // удаляет узел, на который указывает переданный указатель ptr
void del_from_head(ptrNODE& head); // удаляет первый узел в списке, на который указывает переданный указатель head
void del_after(ptrNODE& ptr); // удаляет узел, следующий за узлом, на который указывает переданный указатель ptr

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

/* операции со списком относительно студентов */

// ПОИСК СТУДЕНТА ПО ЗАЧЁТНОЙ КНИЖКЕ
ptrNODE& find(ptrNODE& head);
// УДАЛЕНИЕ СТУДЕНТА
void delete_student(ptrNODE& head);
// ДОБАВЛЕНИЕ СТУДЕНТА С СПИСОК
void create_student(ptrNODE& head);
// ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА
void edit_student(ptrNODE& head);

/* ФУНКЦИИ */

// ПАРСИНГ СЕССИИ (извлечение информации о сессии из строки и преобразует в вектор)
void ParceSession(string& str, vector<Session>& sess);

void Menu(ptrNODE& head);

void Menu(ptrNODE& head)
{
	for (;;) {
		system("cls"); // очистка консоли
		cout << "-------------- Панель Управления --------------" << endl;
		cout << "1. Добавить студента" << endl;
		cout << "2. Удалить студента" << endl;
		cout << "3. Изменить информацию о студенте" << endl;
		cout << "4. Просмотр информации о студентах" << endl;
		cout << "5. Сортировка студентов по оценкам" << endl; // индивидуальное задание
		cout << "0. Выход" << endl;
		/*	Выбор действия
			Т.к. _getch() возвращает значение типа char,
			то, чтобы получить число, нужно из кода ASCII этого символа вычесть код нуля ('0') из таблицы ASCII.
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
		catch (const char* ex) { // определение исключения - строка, переданная в функцию throw
			system("cls");
			cerr << ex;
			Sleep(2000); // задержка на 2 секунды, дабы успели прочитать ошибку, перед тем как оно исчезнет
		}
	}

}long nearestPowerOf2(long N)
{
	long a = log2(N); // вычисление логарифма по основанию 2 (log2)

	if (pow(2, a) == N) // проверка, является ли N степенью двойки
		return N;

	return pow(2, a + 1); // если N не является степенью двойки, то функция вычисляет следующую степень двойки (2^(a+1))
}

// RSA

void RSAKeyGen(long size) { // генерирует public and private keys RSA, используя команды openssl
	long key_size = nearestPowerOf2(size); // полученное значение из N записывается в переменную key_size
	string prompt("openssl genrsa -out key.private "); // генерация ключа RSA, out key.private - сохранение ключа в файл key.private
	prompt += to_string(key_size); // добавляет в конец строки prompt значение key_size
	system(prompt.c_str()); // выполнение команды в командной строке
	prompt = "openssl rsa -in key.private -pubout -out key.public"; // команда для генерации открытого ключа из закрытого ключа
	system(prompt.c_str()); // выполнение команды в командной строке
}

void RSAEncrypt(long size) { // генерирует RSA keys using RSAKeyGen, далее шифрует file.bin, с помощью команды openssl pkeyutl
	RSAKeyGen(size); // генерирует пару открытого и закрытого ключа RSA с помощью функции RSAKeyGen(long size)
	string prompt("openssl pkeyutl -encrypt -pubin -inkey key.public -in file.bin -out file-enc.bin"); // команда для шифрования file.bin с помощью key.public
	/* openssl pkeyut1 используется для операций с ключами (шифрование и дешифрование)
	   -encrypt - указывает на необходимость выполнить операцию шифрования
	   pubin -inkey key.public - указывает на использование открытого ключа, находящегося в файле key.public
	   -in file.bin - указывает на исходный файл шифрования (file.bin)
	   -out file-enc.bin - указывает на имя зашифрованного файла, который будет создан после выполнения команды и будет содержать зашифрованные данные
	*/
	system(prompt.c_str()); // выполнение команды в командной строке
	system("del /f file.bin"); // удаление file.bin без запроса на подтверждение
}

void RSADecrypt() { // расшифровывает file-enc.bin using private key RSA, используя команду openssl pkeyut1
	ifstream f("file.bin", ios_base::binary); // открытие file.bin в bin режиме для чтения, используется для проверки существует ли файл до его расшифровки =>
	                                          // => дабы избежать случайную перезапись существующего файла при расшифровке
	if (f.good()) { // если файл открыт успешно, возвращается true, что означает о том, что файл уже расшифрован
		            // если файл открыт не успешно, то означает, что файл ещё не был расшифрован
		f.close();
		return;
	}
	string prompt("openssl pkeyutl -decrypt -inkey key.private -in file-enc.bin -out file.bin");
	/* pkeyutl - выполнение операций с использованием ключей RSA
	   В данном случае, эта команда указывает openssl расшифровать (-decrypt) содержимое файла file-enc.bin с помощью закрытоо ключа =>
	   => который хранится в файле key.private и записать результат в file.bin
	*/
	system(prompt.c_str()); // выполнение команды в командной строке
	system("del /f file-enc.bin"); // удаление file-enc.bin без запроса на подтверждение удаления
	system("del /f key.public"); // удаление файла key.public с жесткого диска компьютера
	system("del /f key.private"); // удаление файла key.private
	// /f - параметр, который указывает на удаление файла принудительно
}

// AES-256-CBC

string AESKey() { // запрос у пользователя ключа шифрования AES
	cout << "Введите ключ: ";
	return InputString();
}

void AESEncrypt() { // шифрует file.bin using the openssl aes-256-cbc command, используя ключ введённый пользователем
	string prompt("openssl aes-256-cbc -salt -a -e -in file.bin -out file-enc.bin -pass pass:");
	/* aes-256-cbc - алгоритм шифрования
	   -salt - указывает на использование строки соли)))) для усиления шифрования
	   -a - указывает на использование Base64 (стандарт кодирования из .bin в текстовый формат ASCII) для кодировки зашифрованного файла
	   -e - указывает на шифрование файла
	   -in - указывает на имя входного файла (file.bin)
	   -out - указывает на имя выходного файла (file-enc.bin)
	   -pass pass: - указывает на использование пароля (pass:), после которого следует ключ шифрования, введённый пользователем с помощью AESKey()
	*/
	prompt += AESKey(); // добавляет к команде для шифрования файлов openssl aes-256-cbc ключ шифрования, введенный пользователем

	system(prompt.c_str()); // выполнение команды в командной строке
	system("del /f file.bin"); // принудительное удаление file.bin 
}

void AESDecrypt() { // расшифровывает file-enc.bin using the openssl aes-256-cbc command, используя ключ введённый пользователем
	// проверка - если файл изначально не зашифрован, то расшифровки не произойдёт
	ifstream f("file.bin", ios_base::binary);
	if (f) {
		f.close();
		return;
	}
	cout << "Дешифрование...\n";
	string prompt("openssl aes-256-cbc -salt -a -d -in file-enc.bin -out file.bin -pass pass:");
	/* -salt - указывает на использование строки соли)))) для усиления шифрования
	   -a - указывает на использование Base64 (стандарт кодирования из .bin в текстовый формат ASCII) для кодировки зашифрованного файла
	   -d - выполняет дешифрование файла
	   -in file-enc.bin - указывает входной файл, который нужно дешифровать
	   -out file.bin - указывает выходной файл, в который будет записан дешифрованный контент
	   -pass pass: - указывает на использование пароля (pass:), после которого следует ключ шифрования, введённый пользователем с помощью AESKey()
	*/
	prompt += AESKey(); // добавляет к команде для шифрования файлов openssl aes-256-cbc ключ шифрования, введенный пользователем
	system(prompt.c_str()); // выполнение команды в командной строке
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	AESDecrypt(); // дешифрование file-enc.bin 
	ifstream fin("file.bin", ios_base::binary); // открытие file.bin в bin режиме, если открыт успешно, то fin связывается с ifstream =>
	// => если не был найден, то выведет сообщение об ошибке
	if (!fin)
	{
		cout << "Файл не был найден!";
	}
	else {
		ptrNODE head;
		import(fin, head); // импорт из file.bin 
		Menu(head);
		fin.close();
		ofstream fout("file.bin", ios_base::binary); // открытие file.bin для записи данных в bin режиме, если файл существует, он будет перезаписан =>
		// => если файл не существует, он будет создан
		// используется для сохранения списка в файл после того, как он был изменён
		fexport(fout, head); // экспорт в file.bin
		/* если использовать RSA шифрование, то нужно прописать ниже строку, чтобы узнать размер файла.
		Это нужно для последующего создания ключа размером не менее размера файла*/
		// long size = fout.tellp(); // передать size в функцию RSAEncrypt(size)
		fout.close(); // закрываю для того, чтобы сохранить изменения в файле
		clear(head); // очистка памяти
		cout << "Шифрование...\n";
		AESEncrypt(); // шифрование file.bin
		system("cls");
		cout << "Файл был успешно зашифрован!";
	}
	return 0;
}
long nearestPowerOf2(long N)
{
	long a = log2(N); // вычисление логарифма по основанию 2 (log2)

	if (pow(2, a) == N) // проверка, является ли N степенью двойки
		return N;

	return pow(2, a + 1); // если N не является степенью двойки, то функция вычисляет следующую степень двойки (2^(a+1))
}

// RSA

void RSAKeyGen(long size) { // генерирует public and private keys RSA, используя команды openssl
	long key_size = nearestPowerOf2(size); // полученное значение из N записывается в переменную key_size
	string prompt("openssl genrsa -out key.private "); // генерация ключа RSA, out key.private - сохранение ключа в файл key.private
	prompt += to_string(key_size); // добавляет в конец строки prompt значение key_size
	system(prompt.c_str()); // выполнение команды в командной строке
	prompt = "openssl rsa -in key.private -pubout -out key.public"; // команда для генерации открытого ключа из закрытого ключа
	system(prompt.c_str()); // выполнение команды в командной строке
}

void RSAEncrypt(long size) { // генерирует RSA keys using RSAKeyGen, далее шифрует file.bin, с помощью команды openssl pkeyutl
	RSAKeyGen(size); // генерирует пару открытого и закрытого ключа RSA с помощью функции RSAKeyGen(long size)
	string prompt("openssl pkeyutl -encrypt -pubin -inkey key.public -in file.bin -out file-enc.bin"); // команда для шифрования file.bin с помощью key.public
	/* openssl pkeyut1 используется для операций с ключами (шифрование и дешифрование)
	   -encrypt - указывает на необходимость выполнить операцию шифрования
	   pubin -inkey key.public - указывает на использование открытого ключа, находящегося в файле key.public
	   -in file.bin - указывает на исходный файл шифрования (file.bin)
	   -out file-enc.bin - указывает на имя зашифрованного файла, который будет создан после выполнения команды и будет содержать зашифрованные данные
	*/
	system(prompt.c_str()); // выполнение команды в командной строке
	system("del /f file.bin"); // удаление file.bin без запроса на подтверждение
}

void RSADecrypt() { // расшифровывает file-enc.bin using private key RSA, используя команду openssl pkeyut1
	ifstream f("file.bin", ios_base::binary); // открытие file.bin в bin режиме для чтения, используется для проверки существует ли файл до его расшифровки =>
	// => дабы избежать случайную перезапись существующего файла при расшифровке
	if (f.good()) { // если файл открыт успешно, возвращается true, что означает о том, что файл уже расшифрован
		// если файл открыт не успешно, то означает, что файл ещё не был расшифрован
		f.close();
		return;
	}
	string prompt("openssl pkeyutl -decrypt -inkey key.private -in file-enc.bin -out file.bin");
	/* pkeyutl - выполнение операций с использованием ключей RSA
	   В данном случае, эта команда указывает openssl расшифровать (-decrypt) содержимое файла file-enc.bin с помощью закрытоо ключа =>
	   => который хранится в файле key.private и записать результат в file.bin
	*/
	system(prompt.c_str()); // выполнение команды в командной строке
	system("del /f file-enc.bin"); // удаление file-enc.bin без запроса на подтверждение удаления
	system("del /f key.public"); // удаление файла key.public с жесткого диска компьютера
	system("del /f key.private"); // удаление файла key.private
	// /f - параметр, который указывает на удаление файла принудительно
}

// AES-256-CBC

string AESKey() { // запрос у пользователя ключа шифрования AES
	cout << "Введите ключ: ";
	return InputString();
}

void AESEncrypt() { // шифрует file.bin using the openssl aes-256-cbc command, используя ключ введённый пользователем
	string prompt("openssl aes-256-cbc -salt -a -e -in file.bin -out file-enc.bin -pass pass:");
	/* aes-256-cbc - алгоритм шифрования
	   -salt - указывает на использование строки соли)))) для усиления шифрования
	   -a - указывает на использование Base64 (стандарт кодирования из .bin в текстовый формат ASCII) для кодировки зашифрованного файла
	   -e - указывает на шифрование файла
	   -in - указывает на имя входного файла (file.bin)
	   -out - указывает на имя выходного файла (file-enc.bin)
	   -pass pass: - указывает на использование пароля (pass:), после которого следует ключ шифрования, введённый пользователем с помощью AESKey()
	*/
	prompt += AESKey(); // добавляет к команде для шифрования файлов openssl aes-256-cbc ключ шифрования, введенный пользователем

	system(prompt.c_str()); // выполнение команды в командной строке
	system("del /f file.bin"); // принудительное удаление file.bin 
}

void AESDecrypt() { // расшифровывает file-enc.bin using the openssl aes-256-cbc command, используя ключ введённый пользователем
	// проверка - если файл изначально не зашифрован, то расшифровки не произойдёт
	ifstream f("file.bin", ios_base::binary);
	if (f) {
		f.close();
		return;
	}
	cout << "Дешифрование...\n";
	string prompt("openssl aes-256-cbc -salt -a -d -in file-enc.bin -out file.bin -pass pass:");
	/* -salt - указывает на использование строки соли)))) для усиления шифрования
	   -a - указывает на использование Base64 (стандарт кодирования из .bin в текстовый формат ASCII) для кодировки зашифрованного файла
	   -d - выполняет дешифрование файла
	   -in file-enc.bin - указывает входной файл, который нужно дешифровать
	   -out file.bin - указывает выходной файл, в который будет записан дешифрованный контент
	   -pass pass: - указывает на использование пароля (pass:), после которого следует ключ шифрования, введённый пользователем с помощью AESKey()
	*/
	prompt += AESKey(); // добавляет к команде для шифрования файлов openssl aes-256-cbc ключ шифрования, введенный пользователем
	system(prompt.c_str()); // выполнение команды в командной строке
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	AESDecrypt(); // дешифрование file-enc.bin 
	ifstream fin("file.bin", ios_base::binary); // открытие file.bin в bin режиме, если открыт успешно, то fin связывается с ifstream =>
	// => если не был найден, то выведет сообщение об ошибке
	if (!fin)
	{
		cout << "Файл не был найден!";
	}
	else {
		ptrNODE head;
		import(fin, head); // импорт из file.bin 
		Menu(head);
		fin.close();
		ofstream fout("file.bin", ios_base::binary); // открытие file.bin для записи данных в bin режиме, если файл существует, он будет перезаписан =>
		// => если файл не существует, он будет создан
		// используется для сохранения списка в файл после того, как он был изменён
		fexport(fout, head); // экспорт в file.bin
		/* если использовать RSA шифрование, то нужно прописать ниже строку, чтобы узнать размер файла.
		Это нужно для последующего создания ключа размером не менее размера файла*/
		// long size = fout.tellp(); // передать size в функцию RSAEncrypt(size)
		fout.close(); // закрываю для того, чтобы сохранить изменения в файле
		clear(head); // очистка памяти
		cout << "Шифрование...\n";
		AESEncrypt(); // шифрование file.bin
		system("cls");
		cout << "Файл был успешно зашифрован!";
	}
	return 0;
}
