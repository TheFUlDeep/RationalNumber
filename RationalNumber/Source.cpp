#include "RationalNumber.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	RN a;
	a = (1 + RN(1));
	std::cout << a << "\n";

	a *= 2;
	std::cout << a << "\n";

	cout << (RN(1, 2) > a) << endl;

	system("pause");
	return 0;
}