#include "RationalNumber.h"

using namespace std;

//с гугл тестами пока проблема. Надо тогда было делать через assert, но мне лень переписывать

template<typename T>
void LocalCoutRes(const char* str, const T &value, const T &compare, bool thr = true) 
{ 
	cout << str << ". Результат - " << value; 
	if (value == compare) cout << "\nВЕРНО";
	else if (thr) throw std::exception("Проверка не пройдена");
	else cout << "\n НЕверно";
	cout << endl;
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");


	//из-за несколько специфичной функции преобразования дабла в рациональное число RN(2. / 3.) != RN(2,3)
	//cout << RN(2. / 3.) << endl;
	//cout << RN(2,3) << endl;


	LocalCoutRes("Конструктор по умолчанию", RN(),RN(0,1));
	LocalCoutRes("Конструктор c параметром int (-15)", RN(-15),-RN(15));
	LocalCoutRes("Конструктор c параметром double", RN(-1.25),RN(5,-4));
	LocalCoutRes("Конструктор c двумя параметрами (5,-10)", RN(5,-10),RN(-1,2));
	cout << "\n";

	LocalCoutRes("Смена местами числителя и знаменателя (-8/100)", RN(8, -100).InverseCpy(),RN(-100,8));
	LocalCoutRes("Получение целой части (100/5)", RN(100, 5).GetInt(),20);
	LocalCoutRes("Получение дабла (1/2)", RN(1,2).GetDouble(),0.5);
	cout << "\n";
	RN a;
	LocalCoutRes("Присваивание инту (0/1 = 10)", a = 10,RN(10));
	LocalCoutRes("Присваивание даблу (10/1 = 4/100)", a = 4./100., RN(4,100));
	cout << "\n";
	LocalCoutRes("RN+RN (1/25 + 2)", a + RN(2), RN(51,25));
	LocalCoutRes("RN+int (1/25 + 3)", a+3, RN(76,25));
	LocalCoutRes("RN+double (1/25 + 1/50)", a + 1./50., RN(3,50));
	LocalCoutRes("int+RN (1 + 5/10)", 1 + RN(5./10.), RN(3,2));
	LocalCoutRes("double+RN (1/2 + (-5/10))", 1./2. + RN(-5. / 10.), RN());

	cout << "\nОператоры +=, *=, /= реализованы через уже существующие операторы, поэтому их показывать не буду\n\n";

	LocalCoutRes("RN-RN (1/25 - 2)", a - RN(2),RN(-49,25));
	LocalCoutRes("RN-int (1/25 - 3)", a - 3,RN(74,-25));
	LocalCoutRes("RN-double (1/25 - 1/50)", a - 1. / 50.,RN(1,50));
	LocalCoutRes("int-RN (1 - 5/10)", 1 - RN(5. / 10.),RN(1,2));
	LocalCoutRes("double-RN (1/2 - (-5/10))", 1. / 2. - RN(-5. / 10.),RN(1));
	cout << "\n";
	LocalCoutRes("RN*RN (1/25 * 2)", a * RN(2),RN(2,25));
	LocalCoutRes("RN*int (1/25 * 3)", a * 3,RN(3,25));
	LocalCoutRes("RN*double (1/25 * 1/50)", a * 1. / 50.,RN(1,(25*50)));
	LocalCoutRes("int*RN (1 * 5/10)", 1 * RN(5. / 10.),RN(1,2));
	LocalCoutRes("double*RN (1/2 * (-5/10))", 1. / 2. * RN(-5. / 10.),RN(-1,4));
	cout << "\n";
	LocalCoutRes("RN/RN (1/25 / 2)", a / RN(2),RN(1,50));
	LocalCoutRes("RN/int (1/25 / 3)", a / 3,RN(1,75));
	LocalCoutRes("RN/double (1/25 / 1/50)", a / (1. / 50.),RN(50./25.));
	LocalCoutRes("int/RN (1 / 5/10)", 1 / RN(5. / 10.),RN(2));
	LocalCoutRes("double/RN (1/2 / (-5/10))", 1. / 2. / RN(-5. / 10.),RN(-1));

	cout << "\n";
	a = 0;
	LocalCoutRes("(0/1)++", a++,RN());
	cout << a << endl;
	LocalCoutRes("++(1/1)", ++a,RN(2));
	cout << "\n";
	a = 0;
	LocalCoutRes("(0/1)--", a--,RN());
	cout << a << endl;
	LocalCoutRes("--(-1/1)", --a,RN(-2));

	LocalCoutRes("Унарный минус (2/3)", -RN(2,3), RN(-2,3));

	LocalCoutRes("1/2 > 1/4", RN(1./2.) > RN(1./4.), true);
	LocalCoutRes("2/2 > 1/2", RN(2. / 2.) > RN(1. / 2.), true);

	LocalCoutRes("5/10 < 1", RN(5. / 10.) < 1, true);

	system("pause");
	return 0;
}