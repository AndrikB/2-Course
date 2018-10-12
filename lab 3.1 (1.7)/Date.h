#pragma once
#include <iostream>
using std::ostream;
using std::istream;
class interval;

class Date
{
public:
	Date() 
	{
		year = 1;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
		second = 0;
	};
	Date(int y, int mo, int d, int h, int mi, int s)
	{
		year = y;
		month = mo;
		day = d;
		hour = h;
		minute = mi;
		second = s;
		make_correct();
	};


	bool is_intercalary();
	void cout_weekday();
	int weekday();
	Date operator+(interval D2);
	Date operator-(interval D2);
	bool operator==(Date D2);
	bool operator!=(Date D2) { return !(this->operator==(D2)); }
	interval operator-(Date D2);
	friend ostream &operator<<(ostream &os, const Date &d);
	friend istream &operator>>(istream &is, Date &d);
	void write();
	bool is_CE() { make_correct(); return (year > 0); }
private:
	int year, month, day, hour, minute, second;
	void make_correct();
	bool is_correct();
};

class interval 
{
	friend Date;
public:
	interval()
	{
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		second = 0;
	};
	interval(int y, int mo, int d, int h, int mi, int s)
	{
		year = y;
		month = mo;
		day = d;
		hour = h;
		minute = mi;
		second = s;
	};
	void write();

private:
	int year, month, day, hour, minute, second;
	void make_correct();
};

