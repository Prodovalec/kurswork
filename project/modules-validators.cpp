#include "modules-validators.h"

// �������������� ���� ������ �����
int InputInt()
{
    int num;
    while (1) {
        cin >> num;
        /*
            fail() ���������� ��� ������, ��� ������������ �����(����� ��� ��.)
            ����� ������ ����� cin, � ����� ����� � ������� � ������������ �����
        */
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "������������ ���� �����!\n���������� ��� ���:";
            continue;
        }
        return num;
    }
}
// �������������� ���� ������
unsigned short InputMark()
{
    short mark;
    while (1) {
        mark = InputInt(); // ���� ������
        if (mark < 1) mark = 1;
        else if (mark > 5) mark = 5;
        return mark;
    }
}

// �������������� ���� ������
string InputString()
{
    // ���� ������, �������� ������� ��� ������, � �� ����� ������ (ws - whitespace)
    string str;
    getline(cin >> ws, str);
    return str;
}

// �������������� ���� ���� ��������
string InputDate()
{
    /* ��������� ���� ��������. ���� �������� ���� �� ����� ��������������� ������� �������,
       �� ����� ���� ��������� � �������������� ����� ���� */
    //                  day             month           year
    regex reg("([0-2][0-9]|3[0-1]|[0-9]).(0[0-9]|1[0-2]|[0-9]).(199[3-9]|200[0-4])");
    
    string date = InputString();
    if (!regex_match(date, reg)) throw "����������� ������� ���� ��������!";
    return date;
}