#pragma once
#include <iostream>
#include <string>


//знак хранится в числителе

class RN 
{
private:
	int num = 0;
	int denum = 1;

	//private methods
	int GCD(const int, const int)const;
	int LCM(const int, const int)const;
	void Inverse();
	RN InverseCpy()const;
	void Simplify();
	//RN IntToRN(const int);//добавил этот метод для себя для удобства. Не думаю, что он пригодится
	RN DoubleToRN(const double)const;
public:
	RN();
	RN(const int);
	RN(const double);
	RN(const int, const int);

	const int GetInt()const;
	const double GetDouble()const;

	RN& operator=(const RN&);
	RN& operator=(const int);
	RN& operator=(const double);

	RN operator+(const RN&)const;
	RN operator+(const int)const;
	RN operator+(const double)const;
	//когда слева не экземпляр класса, а какой-то другой тип
	friend RN operator+(const int, const RN&);
	friend RN operator+(const double, const RN&);

	RN& operator+=(const RN&);
	RN& operator+=(const int);
	RN& operator+=(const double);

	RN operator-(const RN&)const;
	RN operator-(const int)const;
	RN operator-(const double)const;
	friend RN operator-(const int, const RN&);
	friend RN operator-(const double, const RN&);

	RN& operator-=(const RN&);
	RN& operator-=(const int);
	RN& operator-=(const double);

	RN operator*(const RN&)const;
	RN operator*(const int)const;
	RN operator*(const double)const;
	friend RN operator*(const int, const RN&);
	friend RN operator*(const double, const RN&);

	RN& operator*=(const RN&);
	RN& operator*=(const int);
	RN& operator*=(const double);

	RN operator/(const RN&)const;
	RN operator/(const int)const;
	RN operator/(const double)const;
	friend RN operator/(const int, const RN&);
	friend RN operator/(const double, const RN&);

	RN& operator/=(const RN&);
	RN& operator/=(const int);
	RN& operator/=(const double);

	const RN operator++(int);//это должен быть постфикс
	RN& operator++();

	const RN operator--(int);//это должен быть постфикс
	RN& operator--();

	RN operator-()const;

	bool operator==(const RN&)const;
	bool operator==(const int)const;
	bool operator==(const double)const;
	friend RN operator==(const int, const RN&);
	friend RN operator==(const double, const RN&);

	bool operator!=(const RN&)const;
	bool operator!=(const int)const;
	bool operator!=(const double)const;
	friend RN operator!=(const int, const RN&);
	friend RN operator!=(const double, const RN&);

	bool operator>(const RN&)const;
	bool operator>(const int)const;
	bool operator>(const double)const;
	friend RN operator>(const int, const RN&);
	friend RN operator>(const double, const RN&);

	bool operator<(const RN&)const;
	bool operator<(const int)const;
	bool operator<(const double)const;
	friend RN operator<(const int, const RN&);
	friend RN operator<(const double, const RN&);

	bool operator>=(const RN&)const;
	bool operator>=(const int)const;
	bool operator>=(const double)const;
	friend RN operator>=(const int, const RN&);
	friend RN operator>=(const double, const RN&);

	bool operator<=(const RN&)const;
	bool operator<=(const int)const;
	bool operator<=(const double)const;
	friend RN operator<=(const int, const RN&);
	friend RN operator<=(const double, const RN&);

	friend std::ostream& operator<<(std::ostream&, const RN&);
	friend std::istream& operator>>(std::istream &, RN&);
};