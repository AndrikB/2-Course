#include "Date.h"

bool Date::is_intercalary()
{
	int y = year;
	if (y < 0)y = 1 - year;//it is for BC year

	if (y % 400 == 0)
		return true;
	if (y % 100 == 0)	
		return false;
	if (y % 4 == 0)
		return true;
	 return false;

		
}

bool Date::is_correct() 
{
	if (hour > 23 || minute > 59 || second > 59 || hour < 0 || minute < 0 || second < 0) return false;
	if (month > 12 || month< 0) return false;
	if (day < 0) return false;
	if (month == 2)//feb
		if (day > 28 + this->is_intercalary())
			return false;
		else return true;

	if (month==4|| month == 6 || month == 9 || month == 11)//apr, june, sep, nov
		if (day >30)
			return false;
		else return true;

	if (day > 31)
		return false;
	else
		return true;
}

void Date::make_correct()
{


	while (!this->is_correct())
	{
		if (month > 12) 
		{
			year = year + month / 12;
			month = month % 12;
			if (month == 0)
			{
				month = 12;
				year--;
			}
		}
		//day
		
		if (month == 2)//feb
			if (day > 28 + this->is_intercalary())
			{
				day = day - 28 - this->is_intercalary();
				month++;
				continue;//becouse month may be 14 and it is big problem
			}
			else;
		else if (month == 4 || month == 6 || month == 9 || month == 11)//apr, june, sep, nov
			if (day > 30)
			{
				day = day -30;
				month++;
				continue;
			}
			else;
		else if (day>31)
		{
			day = day - 31;
			month++;
			continue;
		}


	} 
	
}