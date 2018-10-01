#pragma once


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
	};

	bool is_correct();
	bool is_intercalary();
	void make_correct();
	
	void cout_weekday();

private:
	int year, month, day, hour, minute, second;
	int weekday();

};
