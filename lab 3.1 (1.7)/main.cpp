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
	List<string> WeekDay;

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
	iter<int> my_iter = L.begin();
	cout << *my_iter;
	my_iter++;
	cout << *my_iter;
	my_iter++;
	cout << *my_iter;
}



int main()
{
	test1();
	Cycle_List<int> L;
	
	//L.set_mode(3);
	//
	//cout << L.add_tail(5)<<' ';
	//cout << L.add_head(14) << ' ';
	//cout << L.add_tail(24) << ' ';
	//cout << L.add_head(105) << ' ';
	//cout << L.size() << endl << endl;
	//
	//
	//cout << L.search_by_index(L.search_first_with (b<int>)) << endl << endl;
	//cout << L.search_by_index(0) << ' '
	//	<< L.search_by_index(1) << ' '
	//	<< L.search_by_index(2) << ' '
	//	<< L.search_by_index(3) << ' '
	//	<< L.search_by_index(4) << ' '
	//	<< L.search_by_index(5) << endl << endl << endl;
	//L.clean();
	//
	//cout << L.add_tail(5) << ' ';
	//cout << L.add_head(14) << ' ';
	//cout << L.add_tail(24) << ' ';
	//cout << L.add_head(105) << ' ';
	//cout << L.size() << endl << endl;
	//
	//
	//cout << L.search_by_index(L.search_first_with(b<int>)) << endl << endl;
	//
	//L.del_i(L.search_first_with(b<int>));
	//cout << L.search_by_index(L.search_first_with(b<int>)) << endl << endl;
	//cout << L.search_by_index(0) << ' '
	//	<< L.search_by_index(1) << ' '
	//	<< L.search_by_index(2) << ' '
	//	<< L.search_by_index(3) << ' '
	//	<< L.search_by_index(4) << ' '
	//	<< L.search_by_index(5) << endl;

	//Date d(2018, -12, 31	, 0, 0, 0);
	//Date D;
	//interval K;
	//K = d - D;
	//K.write();
	////cout << d.weekday();
	//cout << endl;

	//d.write();
	//cout_weekday(d.weekday());



	system("pause");
	return 0;
}