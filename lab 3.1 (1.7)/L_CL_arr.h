#pragma once
#include "L_CL.h"
#include<thread>
using std::function;
template<typename T>
class L_arr :public L_CL<T>
{
public:
	//конструктори
	L_arr();
	L_arr(int length);
	
	//спільні
	bool add_tail(T d)override;
	bool add_head(T d)override;
	int size()override;
	void clean()override;
	void del_i(int k)override;
	int search_el(T d)override;
	T search_by_index(int k)override;
	int search_first_with (function<bool(T)> f)override;
	
	//деструктор
	~L_arr() { delete[] data; }
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
bool L_arr<T>::add_tail(T d)
{
	if (count == Max-1) return false;
	data[count] = d;
	count++;
	return true;
}

template<typename T>
bool L_arr<T>::add_head(T d)
{
	if (count == Max-1) return false;
	
	for (int i = count; i > 0; i--)
		data[i] = data[i - 1];
	data[0] = d;
	count++;
	return true;
}

template<typename T>
void L_arr<T>::clean() 
{
	index = 0;
	while (count > 0)
	{
		count--;
		data[count] = (T)nullptr;
	}
}

template<typename T>
void L_arr<T>::del_i(int k)
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
T L_arr<T>::search_by_index(int k)
{
	if (k < count&&k >= 0) return data[k];
	return (T)nullptr;
}

template<typename T>
int L_arr<T>::search_first_with (function<bool(T)> f)
{
	for (int i = 0; i < count; i++)
	{
		if (f(data[i])) return i;
	}
	return -1;
}