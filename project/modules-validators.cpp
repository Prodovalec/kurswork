#include "modules-validators.h"

// ВАЛИДИРОВАННЫЙ ВВОД ЦЕЛОГО ЧИСЛА
int InputInt()
{
    int num;
    while (1) {
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
// ВАЛИДИРОВАННЫЙ ВВОД ОЦЕНКИ
unsigned short InputMark()
{
    short mark;
    while (1) {
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
    getline(cin >> ws, str);
    return str;
}

// ВАЛИДИРОВАННЫЙ ВВОД ДАТЫ РОЖДЕНИЯ
string InputDate()
{
    /* Валидация даты рождения. Если введённая дата не будет соответствовать данному шаблону,
       то будет дено сообщение о неккорретности ввода даты */
    //                  day             month           year
    regex reg("([0-2][0-9]|3[0-1]|[0-9]).(0[0-9]|1[0-2]|[0-9]).(199[3-9]|200[0-4])");
    
    string date = InputString();
    if (!regex_match(date, reg)) throw "Некорректно введена дата рождения!";
    return date;
}