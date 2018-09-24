#pragma once
#include "List.h"

template<typename T>
class L_arr ://public L_CL<T>
{
	public
		L_arr();
		L_arr(int length);
		bool add_L(T d);
		int size();
		void del_all_L();
		void del_i_L(int i);
		int search_el(T d);
		T search_i_el(int k);
		~L_CL_arr() { delete data[] }
	//////////////
	private
		T *data = nullptr;
		int index;
		int N;
};

template<typename T>
L_arr<T>::L_arr()
{
	N = 1000;
	index = 0;
	data = new T[N];
}

template<typename T>
L_arr<T>::L_arr(int length)
{
	N = length;
	index = 0;
	data = new T[N];
}

template<typename T>
int L_arr<T>::size()
{
	return index;
}

template<typename T>
bool L_arr<T>::add_L(T d)
{
	if (index < N) return false;
	data[i] = d;
	i++;
	return true;
}

template<typename T>
void L_arr<T>::del_all_L() 
{
	while (i > 0)
	{
		i--;
		data[i] = nullptr;
	}
}

template<typename T>
void L_arr<T>::del_i_L(int k)
{
	if (k >= i) return;
	for (int j = k; j < i; j++)
	{
		data[j] = data[j + 1];
	}
	i--;
}

template<typename T>
int L_arr<T> ::search_el(T d)
{
	int k = 0;
	while (k<i)
	{
		if (d == data[k])return k;
	}
	std::cout << "isnt here" << std::endl;
	return -1;
}

template<typename T>
T L_arr<T>::search_i_el(int k)
{
	return data[k];
}
