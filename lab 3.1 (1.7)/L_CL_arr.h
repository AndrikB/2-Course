#pragma once
#include "L_LC.h"

template<typename T>
class L_arr :public L_CL<T>
{
public:
	//конструктори
	L_arr();
	L_arr(int length);
	
	//спільні
	bool add_L(T d);
	int size();
	void del_all_L();
	void del_i_L(int k);
	int search_el(T d);
	T search_i_el(int k);
	
	//деструктор
	~L_arr() { delete data[]; }
	//////////////
private:
	T *data = nullptr;// масив
	int count;//к-ть елементів зара
	int index;//позиція даного елемента 
	int Max;//максимаьна кількість
};

template<typename T>
L_arr<T>::L_arr()
{
	Max = 1000;
	count = 0;
	int index = 0;
	data = new T[Max];
}

template<typename T>
L_arr<T>::L_arr(int length)
{
	Max = length;
	count = 0;
	index = 0;
	data = new T[Max];
}

template<typename T>
int L_arr<T>::size()
{
	return count;
}

template<typename T>
bool L_arr<T>::add_L(T d)
{
	if (count == Max) return false;
	data[count] = d;
	count++;
	return true;
}

template<typename T>
void L_arr<T>::del_all_L() 
{
	index = 0;
	while (count > 0)
	{
		count--;
		data[count] = nullptr;
	}
}

template<typename T>
void L_arr<T>::del_i_L(int k)
{
	if (k >= count) return;
	for (int j = k; j < count; j++)
	{
		data[j] = data[j + 1];
	}
	count--;
}

template<typename T>
int L_arr<T> ::search_el(T d)
{
	int k = 0;
	while (k<count)
	{
		if (d == data[k])return k;
	}
	std::cout << "isnt here" << std::endl;
	return -1;
}

template<typename T>
T L_arr<T>::search_i_el(int k)
{
	if (k<count) return data[k];
	return nullptr;
}
