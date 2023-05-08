#pragma once
// подключение всех необходимых библиотек
#include <iostream>		// console input/output
#include <Windows.h>	// Sleep & consoleCP
#include <fstream>		// file input/output
#include <string>		// string
#include <vector>		// работа с вектором
#include <map>			// работа со словарЄм
#include <regex>		// регул€рные выражени€ (валидаци€ даты рождени€)
#include <conio.h>		// _getch() (функци€ дл€ моментального считывани€ введЄнного символа через консоль)
#include <iomanip>		// форматирование вывод в консоль

using namespace std;

int InputInt();
unsigned short InputMark();
string InputString();
string InputDate();