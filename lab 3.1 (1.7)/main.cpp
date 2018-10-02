#include <iostream>
#include "L_CL_arr.h"
#include "L_CL_list.h"
#include "L_CL_vector.h"
#include <string>
#include<utility>
#include "L_CL.h"

#include "List.h"
#include "Cycle_List.h"

#include "Date.h"

#include<thread>
#include"iterator.h"

using std::cout;
using std::endl;
using std::function;
using std::string;



void cout_weekday(int count)
{
	if (count < 0)
	{
		cout << "The date isnt correct" << endl;
		return;
	}
	Cycle_List<string> WeekDay;
	WeekDay.set_mode(2);
	WeekDay.add_tail("Sunday");
	WeekDay.add_tail("Monday");
	WeekDay.add_tail("Tuesday");
	WeekDay.add_tail("Wednesday");
	WeekDay.add_tail("Thursday");
	WeekDay.add_tail("Friday");
	WeekDay.add_tail("Saturday");
	

	cout << WeekDay[count] << endl;
}

//it is only for function<bool<T>>
template <typename T>
bool b(T d)
{
	if (d % 4 == 0)return true;
	return false;
}


void test1() 
{
	/*Cycle_*/List<int> L;
	L.set_mode(2);

	L.add_tail(5);
	L.add_head(14);
	L.add_tail(24);
	L.add_head(105);
	L.add_tail(33);
	L.add_head(77);
	iter<int> my_iter = L.begin();
	cout << *my_iter<<' ';
	my_iter+=2;
	cout << *my_iter << ' ';
	my_iter++;
	cout << *my_iter << ' ';
	my_iter++;
	cout << *my_iter << ' ';
	cout << endl;
}

void test2()
{
	Date d(2018, -12, 31, 0, 0, 0);
	Date D;
	interval K;
	K = d - D;
	K.write();

	cout << endl;
	d.write();
	cout_weekday(d.weekday());///==d.cout_weekday();
	cout << endl;
}

void test3()
{
	List<Date> L;
	Date d(2018, -12, 31, 0, 0, 0);
	Date D;
	interval K;
	K = d - D;
	Date D2;
	D2 = d + K;
	Date D3;
	D3 = D2 + K;
	L.add_head(D2);
	L.add_head(D);
	L.add_head(D3);
	L[2].write();
	
}

int main()
{
	test3();
	Cycle_List<int> L;
	

	system("pause");
	return 0;
}