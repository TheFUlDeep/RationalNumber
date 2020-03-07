#include "RationalNumber.h"

using namespace std;

int RN::GCD(const int a, const int b)const
{
	int mya = (a > 0) ? a : (-a);
	int myb = (b > 0) ? b : (-b);
	while (mya != 0 && myb != 0)
	{
		if (mya > myb) mya = mya % myb;
		else myb = myb % mya;
	}
	return (mya + myb);
}

int RN::LCM(const int a, const int b) const { return a * b / GCD(a, b); }

void RN::Inverse()
{
	if (num == 0) throw std::exception("denum can't be a zero");
	int tmp = num;
	num = denum;
	denum = tmp;
	if (denum < 0) { denum = -denum; num = -num; }
}

RN RN::InverseCpy() const
{
	RN tmpRN(*this);
	tmpRN.Inverse();
	return tmpRN;
}

void RN::Simplify()
{
	int gcd = GCD(num, denum);
	if (gcd == 1 || gcd == 0) return;
	num /= gcd;
	denum /= gcd;
}

//RN RN::IntToRN(const int a) { return RN(a); }

RN RN::DoubleToRN(const double a)const
{
	bool minus = a < 0;
	int intpart = int(a);//беру только целую часть от дабла
	intpart = (intpart > 0) ? intpart : (-intpart);//беру это число по модулю
	//я не придумал, как нормально поместить в инт все, что идет после точки (так как там число флотовое), поэтому сделал костыль через стринг
	string stringdouble = to_string(a);
	stringdouble = stringdouble.substr(stringdouble.find(',') + 1);
	
	//избавляюсь от нулей в конце
	while (stringdouble[stringdouble.length()-1] == '0') { 
		stringdouble = stringdouble.substr(0, stringdouble.length() - 1); 
	}
	int len = (int)stringdouble.length();
	int intfractpart = stoi(stringdouble);

	int denum1 = int(pow(10, len));
	RN newRN(intpart * denum1 + intfractpart, denum1);
	if (minus) newRN.num = -newRN.num;
	newRN.Simplify();
	return newRN;
}

RN::RN() = default;

RN::RN(const int num1) { num = num1; }

RN::RN(const double a)
{
	RN tmpRN = DoubleToRN(a);
	num = tmpRN.num;
	denum = tmpRN.denum;
}

RN::RN(const int num1, const int denum1)
{
	if (denum1 == 0) throw std::exception("denum can't be a zero");

	if (!(denum1 < 0 && num1 < 0) && (num1 < 0 || denum1 < 0))
	{
		//если дробь отрицательная
		denum = (denum1 > 0) ? denum1 : (-denum1);
		num = (num1 > 0) ? (-num1) : num1;//если num >0 то умножаем на -1, если <=0, то так и оставляем
	}
	else
	{
		//если дробь положительная
		denum = denum1;
		num = num1;
	}
	Simplify();
}

const int RN::GetInt() const { return int(num / denum); }

const double RN::GetDouble() const { return (double(num) / double(denum)); }

RN & RN::operator=(const RN &other)
{
	num = other.num;
	denum = other.denum;
	return *this;
}

RN & RN::operator=(const int a)
{
	denum = 1;
	num = a;
	return *this;
}

RN & RN::operator=(const double a)
{
	*this = RN(DoubleToRN(a));
	return *this;
}

RN RN::operator+(const RN &otherRN) const
{
	if (denum == otherRN.denum) {
		RN res(num + otherRN.num, denum);
		return res;
	}
	else
	{
		int lcm = LCM(denum, otherRN.denum);
		int thisdenum, thisnum, otherdenum, othernum;
		if (denum != lcm) 
		{ 
			int multiplier = lcm / denum;
			thisdenum = denum * multiplier;
			thisnum = num * multiplier;
		} 
		else { thisdenum = denum; thisnum = num; }
		if (otherRN.denum != lcm) 
		{ 
			int multiplier = lcm / otherRN.denum;
			otherdenum = otherRN.denum * multiplier;
			othernum = num * multiplier;
		} 
		else { otherdenum = otherRN.denum; othernum = otherRN.num; }
		RN res(thisnum + othernum, thisdenum);
		return res;
	}
}

RN RN::operator+(const int a) const { return (*this + RN(a)); }

RN RN::operator+(const double a) const {return (*this + RN(a));}

RN & RN::operator+=(const RN &rn) { *this = *this + rn; return *this; }

RN & RN::operator+=(const int a) { *this = *this + a; return *this; }

RN & RN::operator+=(const double a) { *this = *this + a; return *this; }

RN RN::operator-(const RN &otherRN) const
{
	//привести к общему знаменателю и вычесть
	//копипаста оператора+ только изменен знак
	if (denum == otherRN.denum) {
		RN res(num - otherRN.num, denum);
		res.Simplify();
		return res;
	}
	else
	{
		int lcm = LCM(denum, otherRN.denum);
		int thisdenum, thisnum, otherdenum, othernum;
		if (denum != lcm)
		{
			int multiplier = lcm / denum;
			thisdenum = denum * multiplier;
			thisnum = num * multiplier;
		}
		else { thisdenum = denum; thisnum = num; }
		if (otherRN.denum != lcm)
		{
			int multiplier = lcm / otherRN.denum;
			otherdenum = otherRN.denum * multiplier;
			othernum = num * multiplier;
		}
		else { otherdenum = otherRN.denum; othernum = otherRN.num; }
		RN res(thisnum - othernum, thisdenum);
		res.Simplify();
		return res;
	}
}

RN RN::operator-(const int a) const { return (*this - RN(a)); }

RN RN::operator-(const double a) const { return (*this - RN(a)); }

RN & RN::operator-=(const RN &rn) { *this = *this - rn; return *this; }

RN & RN::operator-=(const int a) { *this = *this - a; return *this; }

RN & RN::operator-=(const double a) { *this = *this - a; return *this; }

RN RN::operator*(const RN &rn) const { RN res(num*rn.num, denum*rn.denum); res.Simplify(); return res; }

RN RN::operator*(const int a) const { return (*this * RN(a)); }

RN RN::operator*(const double a) const { return (*this * RN(a)); }

RN & RN::operator*=(const RN &rn) { *this = *this * rn; return *this; }

RN & RN::operator*=(const int a) { *this = *this * a; return *this; }

RN & RN::operator*=(const double a) { *this = *this * a; return *this; }

RN RN::operator/(const RN &rn) const { return (*this * rn.InverseCpy()); }

RN RN::operator/(const int a) const { return (*this / RN(a)); }

RN RN::operator/(const double a) const { return (*this / RN(a)); }

RN & RN::operator/=(const RN &rn) { *this = *this / rn; return *this; }

RN & RN::operator/=(const int a) { *this = *this / a; return *this; }

RN & RN::operator/=(const double a) { *this = *this / a; return *this; }

const RN RN::operator++(int)
{
	RN tmpRN(*this);
	operator+=(1);
	return tmpRN;
}

RN & RN::operator++() { operator+=(1); return *this; }

const RN RN::operator--(int)
{
	RN tmpRN(*this);
	operator-=(1);
	return tmpRN;
}

RN & RN::operator--() { operator-=(1); return *this; }

RN RN::operator-()const
{
	RN res = *this;
	res.num = -num;
	return res;
}

bool RN::operator==(const RN &rn) const {return GetDouble() == rn.GetDouble();}

bool RN::operator==(const int a) const { return GetDouble() == a; }

bool RN::operator==(const double a) const { return GetDouble() == a; }

bool RN::operator!=(const RN &rn) const { return (operator==(rn) == false); }

bool RN::operator!=(const int a) const { return (operator==(a) == false); }

bool RN::operator!=(const double a) const { return (operator==(a) == false); }

bool RN::operator>(const RN &rn) const { return GetDouble() > rn.GetDouble(); }

bool RN::operator>(const int a) const { return GetDouble() > a; }

bool RN::operator>(const double a) const { return GetDouble() > a; }

//operator< сделаю НЕ через существующие операторы, чтобы программе выполнять меньше действий
bool RN::operator<(const RN &rn) const { return GetDouble() > rn.GetDouble(); }

bool RN::operator<(const int a) const { return GetDouble() < a; }

bool RN::operator<(const double a) const { return GetDouble() < a; }

bool RN::operator>=(const RN &rn) const { return (operator<(rn) == false); }

bool RN::operator>=(const int a) const { return (operator<(a) == false); }

bool RN::operator>=(const double a) const { return (operator<(a) == false); }

bool RN::operator<=(const RN &rn) const { return (operator>(rn) == false); }

bool RN::operator<=(const int a) const { return (operator>(a) == false); }

bool RN::operator<=(const double a) const { return (operator>(a) == false); }

std::ostream & operator<<(std::ostream &out, const RN &rn) { out << rn.num << '/' << rn.denum; return out; }

std::istream & operator>>(std::istream &in, RN &rn)
{
	char buf[255];
	in.getline(buf, 255);
	rn = atof(buf);
	return in;
}

RN operator+(const int left, const RN &right) { return right.operator+(left); }

RN operator+(const double left, const RN &right) { return right.operator+(left); }

RN operator-(const int left, const RN &right) { return right.operator+(-left); }

RN operator-(const double left, const RN &right) { return right.operator+(-left); }

RN operator*(const int left, const RN &right) { return right.operator*(left); }

RN operator*(const double left, const RN &right) { return right.operator*(left); }

RN operator/(const int left, const RN &right) { return right.InverseCpy().operator*(left); }

RN operator/(const double left, const RN &right) { return right.InverseCpy().operator*(left); }

RN operator==(const int left, const RN &right) { return right.operator==(left); }

RN operator==(const double left, const RN &right) { return right.operator==(left); }

RN operator!=(const int left, const RN &right) { return right.operator!=(left); }

RN operator!=(const double left, const RN &right) { return right.operator!=(left); }

RN operator>(const int left, const RN &right) { return right.operator<(left); }

RN operator>(const double left, const RN &right) { return right.operator<(left); }

RN operator<(const int left, const RN &right) { return right.operator>(left); }

RN operator<(const double left, const RN &right) { return right.operator>(left); }

RN operator>=(const int left, const RN &right) { return right.operator<=(left); }

RN operator>=(const double left, const RN &right) { return right.operator<=(left); }

RN operator<=(const int left, const RN &right) { return right.operator>=(left); }

RN operator<=(const double left, const RN &right) { return right.operator>=(left); }