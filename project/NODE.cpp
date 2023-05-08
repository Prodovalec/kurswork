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

/* �������� ���������� */

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

/* �������� �������� */

// �������� �� ���������
void delete_by_pointer(ptrNODE& ptr)
{
	ptrNODE p = ptr;
	ptr = p->next;
	delete p;
}

// �������� �� ������ ������
void del_from_head(ptrNODE& head)
{
	/*ptrNODE P = head;
	head = p -> next;
	delete p;*/
	delete_by_pointer(head);
}

// �������� �������� ����� ���������
void del_after(ptrNODE& ptr)
{
	/*ptrNODE p = ptr -> next;
	ptr -> next = p -> next;
	delete p;*/
	delete_by_pointer(ptr->next);
}

// ������� ������
void clear(ptrNODE& head)
{
	while (head)
		del_from_head(head);
}
/* �������� ��� ������ */

// ����� ������ � �������
void print(ptrNODE head)
{
	if (!head) { // �������� ������
		std::cout << "������ ����!\n";
	}
	else
	{
		std::cout << left << setw(12) << "�������" << " | " << setw(10) << "���" << " | " << setw(12) << "��������" << " | ";
		std::cout << setw(10) << "���� ����." << " | " << setw(15) << "��� �����������" << " | " << setw(10) << "���������";
		std::cout << " | "  << setw(7)<< "�������" << " | " << setw(10) << "������" <<  " | " << setw(17) << "� �������� ������" << " | " << setw(3) << "���" << endl;
		ptrNODE p = head;
		while (p)
		{	// ��������������� ����� ���������� � ��������
			std::cout << left << setw(12) << p->data.surname << " | " << setw(10) << p->data.name << " | " << setw(12) << p->data.patronimyc << " | ";
			std::cout << setw(10) << p->data.birth.GetDate() << " | " << setw(15) << p->data.admision_year << " | " << setw(10) << p->data.faculty;
			std::cout << " | " << setw(7) << p->data.department << " | " << setw(10) << p->data.group << " | " << setw(17) << p->data.record_book << " | " << setw(3) << (p->data.sex ? "���" : "���") << endl;
			// ����� ���� ������
			int c = 0;
			for (auto cur : p->data.sessions) {
				std::cout << ++c <<"-� �������\n";
				std::cout << cur.GetAllSub() << endl;
			}
			p = p->next;
			std::cout << '\n';
		}
	}
}

// ���������� ������������ ������ ������������ ���������� ��Ҩ��� � ������ �������� (�� ��������)
// ���������� ������� ������� (INSERTION SORT)
void sort_by_marks(ptrNODE& head)
{
	if (!head) { // �������� ������
		std::cout << "������ ����!\n";
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

// ������ ������ �� ����� � ������
void import(ifstream& fin, ptrNODE& head)
{
	init(head); // ������������� ������ (�������)
	string line;
	ptrNODE tail = head; // �������� ��������� �� "�����" �������
	while (getline(fin, line))
	{
		DATA data;
		string delimiter = " ", token;
		size_t pos = 0, count = 0;
		// ������� ���� ������ line
		while ((pos = line.find(delimiter)) != string::npos || pos + 1 != line.length())
		{
			token = line.substr(0, pos);
			// ������ ���� ���������� � DATA �� ������ ������������ ������
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
				data.sex = (token == "���" ? true : false);
				break;
			default:
				break;
			}
			line.erase(0, pos + delimiter.length());
			// ���������� ������ � DATA
			count++;
			if (line[0] == '[') // ������� ����������� ������ ������������ ������
			{
			ParceSession(line, data.sessions);
			}
		}
		add_after(tail, data);
		tail = tail->next;
	}
	del_from_head(head); 
}
// ������� ������ � ����
void fexport(ofstream& out, ptrNODE& head)
{
	ptrNODE temp = head;
	while (temp) {
		out << temp->data.DataToString() << "\n";
		temp = temp->next;
	}
}


// �������� ��������
void delete_student(ptrNODE& head) {
	std::cout << "������� ����� �������� ������: ";
	int book = InputInt();
	if (book == 0) return;
	if (to_string(book).length() != 7)
		throw "������������ ���� �������� ������!";
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
	throw "� ������ ��� �������� � ����� ������� �������� ������!";
}

// ���������� �������� � ������
void create_student(ptrNODE& head)
{
	// ���������������� ���� ���������� � ��������
	DATA data;
	std::cout << "�������: ";
	data.surname = InputString();
	std::cout << "���: ";
	data.name = InputString();
	std::cout << "��������: ";
	data.patronimyc = InputString();
	std::cout << "���� ��������: ";
	data.birth = InputDate();
	std::cout << "��� �����������: ";
	data.admision_year = InputInt();
	if (data.admision_year > 2023 || data.admision_year < 2013)
		throw "����� ������������ ���!";
	std::cout << "���������: ";
	data.faculty = InputString();
	std::cout << "�������: ";
	data.department = InputString();
	std::cout << "������: ";
	data.group = InputString();
	std::cout << "����� �������� ������: ";
	data.record_book = InputInt();
	if (data.record_book / 1000 != data.admision_year && to_string(data.record_book).length() != 7)
		throw "������������ ���� �������� ������!";
	std::cout << "���: ";
	string sex = InputString();
	(sex.find('���') != string::npos) ?data.sex = 1: data.sex = 0;
	std::cout << "������� ���������� ���������: ";
	int csess = InputInt();
	if (csess < 1 || csess > 10) throw "������������ ���� ���������� ���������!";
	// ���� ���������� �� ���� ���������
	for (size_t i = 0; i < csess; i++)
	{
		std::cout << i+1 << "-� �������\n";
		Session temp;
		try {
			while (1) {
				std::cout << "������� �������� ��������: ";
				string subj = InputString();
				std::cout << "������� ������: ";
				int mark = InputMark();
				temp.AddSubject(subj, mark);
				std::cout << "������� ����������? (��\\���)";
				subj = InputString();
				if (subj == "���") break;
			}
		}
		catch (char* exp) {
			cerr << exp;
		}
		data.sessions.push_back(temp);
	}
	add_head(head, data);
}
// ��������� ������ ��������
void edit_student(ptrNODE& head) {
	ptrNODE temp = find(head);
	std::cout << "��� �� ������ ��������?\n";
	std::cout << "1. �������\n2. ���\n3. ��������\n4. ���� ��������\n5. ��� �����������\n6. ���������";
	std::cout << "\n7. ����� �������� ������\n8. ���������� �� ������\n0. �����\n";
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
		if (temp->data.admision_year > 2023 || temp->data.admision_year < 2013) throw "����� ������������ ���!";
		break;
	case 6:
		temp->data.faculty = InputString();
		temp->data.department = InputString();
		temp->data.group = InputString();
		break;
	case 7:
		temp->data.record_book = InputInt();
		if (temp->data.record_book / 1000 != temp->data.admision_year && to_string(temp->data.record_book).length() != 7)
			throw "������������ ���� �������� ������!";
		break;
	case 8:
	{
		std::cout << "������� ����� ��������: ";
		int sem = InputInt();
		if (sem < 0 || sem > temp->data.sessions.size()) throw "������������ ���� ������ ��������!";
		std::cout << "������� �������� ��������: ";
		string subj = InputString();
		map<string, int> ::iterator it = temp->data.sessions[sem].GetSubjects().find(subj);
		if (it == temp->data.sessions[sem].GetSubjects().end()) {
			throw "������ �������� ��� � ������ ������!";
		}
		else {
			std::cout << "��������� �������� � " << it->first << " ��: ";
			it->second = InputMark();
		}
	}
		break;
	default:
		std::cout << "������ ������ �� ��������������!";
		break;
	}
}
// ����� �������� �� ��ר���� ������
ptrNODE& find(ptrNODE& head)
{
	std::cout << "������� ����� �������� ������: ";
	int book = InputInt();
	if (to_string(book).length() != 7)
		throw "������������ ���� �������� ������!";
	ptrNODE temp = head;
	while (temp)
	{
		if (temp->data.record_book == book)
			return temp;
		temp = temp->next;
	}
	throw "� ������ ��� �������� � ����� ������� �������� ������!";
}
// ������� ������ (������)
void ParceSession(string& str, vector<Session>& sess)
{
	size_t csubj = 0, pos;
	while (str.size() > 0) {
		if (str[0] == '\r') {
			str.clear();
			break;
		}
		str.erase(0, 2); // �������� "["
		Session temp; // �������� ������� ��� ����� ���������� � �������
		// ������� ����� � ��������, ������������ "[]"
		while (((pos = str.find_first_of("12345")) != string::npos) && str[0] != '[') {
			temp.AddSubject(str.substr(0, pos - 1), str[pos] - '0');
			// �������� ����������� ����� ������
			str[pos + 2] == ']' ? str.erase(0, pos + 4) : str.erase(0, pos + 2);
		}
		sess.push_back(temp);
	}
}