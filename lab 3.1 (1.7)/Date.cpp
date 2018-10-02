#include "Date.h"
#include <iostream>
bool intercalary(int y)
{
	if (y < 0)y = 1 - y;//it is for BC year

	if (y % 400 == 0)
		return true;
	if (y % 100 == 0)	
		return false;
	if (y % 4 == 0)
		return true;
	 return false;
}

bool Date::is_intercalary()
{
	return intercalary(year);
}

int day_in_month(int year, int month)
{
	if (month == 2) return 28 + intercalary(year);//feb
	if (month == 4 || month == 6 || month == 9 || month == 11) return 30;//apr, june, sep, nov
	return 31;
}

bool Date::is_correct() 
{
	if (hour > 23 || minute > 59 || second > 59 || hour < 0 || minute < 0 || second < 0) return false;
	if (month > 12 || month< 0) return false;
	if (day < 0) return false;

	if (day > day_in_month(year, month))return false;
	else return true;
}

void Date::make_correct()
{

	while (month < 1)
	{
		month += 12;
		year--;
	}
	while (month > 12)
	{
		month -= 12;
		year++;
	}

	while (day < 1)
	{
		month--;
		if (month < 1)
		{
			month += 12;
			year--;
		}
		day += day_in_month(year, month);
	}
	while (day > day_in_month(year, month))
	{
		day -= day_in_month(year, month);
		month++;
		if (month > 12)
		{
			month -= 12;
			year++;
		}
	}

}

int Date::weekday() 
{
	if (!this->is_correct()) return -1;
	int count = 1;
	if (year > 0)
	{
		for (int i = 1; i < year; i++)
			if (intercalary(i))count += 2;//in intercalary years weekday shifts on 2 days
			else count+=1;
		
		for (int i = 1; i < month; i++)
			count += day_in_month(year, i);
		count = count + day - 1;
		

	}
	else //it is for BC year
	{
		return -1;
		//for (int i = -1; i > year; i--)
		//	if (intercalary(i))count -= 2;//in intercalary years weekday shifts on 2 days
		//	else count -= 1;
		//
		//for (int i = 1; i < month; i++)
		//	count -= day_in_month(year, i);
		//count = count - day + 1;
		//
	}
	return count;
}


void Date::cout_weekday()
{
	int count = weekday();
	if (count < 0)
	{
		std::cout << "The date isnt correct for now" << std::endl;
		return;
	}

	count = count % 7;
	switch (count)
	{												
	case 1: std::cout << "Monday"; break; 
	case 2: std::cout << "Tuesday"; break;
	case 3: std::cout << "Wednesday"; break;
	case 4: std::cout << "Thursday"; break;
	case 5: std::cout << "Friday"; break; 
	case 6: std::cout << "Saturday"; break;
	case 0: std::cout << "Sunday"; break;
	default:
		std::cout << "The date isnt correct";
		break;
	}
	std::cout << std::endl;
}

Date Date::operator+(interval D2)
{
	Date D3(year+D2.year, month + D2.month, day + D2.day, hour + D2.hour, minute + D2.minute, second + D2.second );
	D3.make_correct();
	return D3;
}

Date Date::operator-(interval D2)
{
	Date D3(year - D2.year, month - D2.month, day - D2.day, hour - D2.hour, minute - D2.minute, second - D2.second);
	D3.make_correct();
	return D3;
}

interval Date::operator-(Date D2) 
{
	interval T(year - D2.year, month - D2.month, day - D2.day, hour - D2.hour, minute - D2.minute, second - D2.second);
	T.make_correct();
	return T;
}

bool Date::operator==(Date D2)
{
	if (this->year != D2.year) return false;
	if (this->month != D2.month) return false;
	if (this->day != D2.day) return false;
	if (this->hour != D2.hour) return false;
	if (this->minute != D2.minute) return false;
	if (this->second != D2.second) return false;
	return true;
}

void  Date::write() { std::cout << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << minute << ' ' << second << std::endl; }

void interval::make_correct()
{

	while (month < 1)
	{
		month += 12;
		year--;
	}
	while (month > 12)
	{
		month -= 12;
		year++;
	}

	while (day < 1)
	{
		month--;
		if (month < 1)
		{
			month += 12;
			year--;
		}
		day += day_in_month(year, month);
	}
	while (day > day_in_month(year, month))
	{
		day -= day_in_month(year, month);
		month++;
		if (month > 12)
		{
			month -= 12;
			year++;
		}
	}

}

void interval::write() { std::cout << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << minute << ' ' << second << std::endl; }