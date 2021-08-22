#include <iostream>
#include "SLA.h"
#include "HUF.h"
#include "ZAG.h"
using namespace std;

void dialogMain()
{
	void (*listOfMethods[26])() 
	{	
		dialogSLA, dialogHUF, dialogZAG, NULL, NULL, 
		NULL, NULL, NULL, NULL, NULL, 
		NULL, NULL, NULL, NULL, NULL, 
		NULL, NULL, NULL, NULL, NULL, 
		NULL, NULL, NULL, NULL, NULL, NULL
	};
	cout	<< "Введите номер задания: \n"
			<< "\nПростые линейные уравнения \t 1"
			<< "\nЖадный алгоритм Хаффмана \t 2"
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
	dialogMain();
	return 0;
}


