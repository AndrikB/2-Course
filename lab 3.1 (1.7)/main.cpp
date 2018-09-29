#include <iostream>
#include "L_CL_arr.h"
#include "L_CL_list.h"
#include "L_CL_vector.h"

#include "L_CL.h"

#include "List.h"

#include <functional>
#include<thread>

using std::cout;
using std::endl;
using std::function;

//template <typename T>
bool b(int d)
{
	if (d % 4 == 0)return true;
	return false;
}

//template <>
//bool b</*назва класу*/>(/*назва класу*/ d)
//{
//	if (d < 50)return true;
//	return false;
//}


int main()
{
	List<int> L;

		{
		cout << L.add_tail(5)<<' ';
		cout << L.add_head(14) << ' ';
		cout << L.add_tail(24) << ' ';
		cout << L.add_head(105) << ' ';
		cout << L.size() << endl; 
	}


	cout << L.search_by_index(L.search_first_with (b));
	cout << L.search_by_index(0) << ' '
		<< L.search_by_index(1) << ' '
		<< L.search_by_index(2) << ' '
		<< L.search_by_index(3) << ' '
		<< L.search_by_index(4) << endl;
	system("pause");
	return 0;
}