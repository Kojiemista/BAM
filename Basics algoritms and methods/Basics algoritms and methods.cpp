#include <iostream>
#include "SLA.h"
#include <string>
using namespace std;

void dialog()
{
	void (*listOfMethods[10])() { dialogSLA, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	cout << "Введите номер задания: \n"
		<< "\nПростые линейные уравнения \t 1"
		<< "\nПростые линейные уравнения \t 2"
		<< "\nПростые линейные уравнения \t 3"
		<< "\nПростые линейные уравнения \t 4"
		<< "\nПростые линейные уравнения \t 5"
		<< "\nПростые линейные уравнения \t 6"
		<< "\nПростые линейные уравнения \t 7"
		<< "\nПростые линейные уравнения \t 8"
		<< "\nПростые линейные уравнения \t 9"
		<< "\nПростые линейные уравнения \t 10\n"
		<< "\n№: ";
	short tmp;
	cin >> tmp;
	--tmp;
	if (listOfMethods[tmp] == nullptr || tmp > (sizeof(listOfMethods) / 4) - 1 || tmp < 0) return;
	else listOfMethods[tmp]();
	return;
}

int main()
{
	setlocale(LC_ALL, "rus");
	dialog();
	return 0;
}


