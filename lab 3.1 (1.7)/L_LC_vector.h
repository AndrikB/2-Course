#pragma once
#include "L_LC.h"
#include <vector>
#include<thread>
using std::function;
using std::vector;

template<typename T>
class L_vector :public L_vector<T>
{
public:
	//конструктори
	

	//спільні
	bool add_L(T d);
	int size();
	void del_all_L();
	void del_i_L(int k);
	int search_el(T d);
	T search_i_el(int k);

	//деструктор

	/////////////////
private:
	vector<T> data;

};

template<typename T>
bool L_vector<T>::add_L(T d) 
{
	data.push_back(d);
	return true;
}

template<typename T>
int L_vector<T>::size()
{
	return data.size();
}

template<typename T>
void L_vector<T>::del_all_L()
{
	data.clear();
}

template<typename T>
void L_vector<T>::del_i_L(int k)
{
	data.erase(data.begin() + k);
}

template<typename T>
int  L_vector<T>::search_el(T d)
{
	int s = data.size;
	for (int i = 0; i < s; i++)
	{
		if (d == data[i])
			return i;
	}
	return -1;
}

template<typename T>
T L_vector<T>::search_i_el(int k)
{
	if (k < data.size&&k >= 0) return data[k];
	return nullptr;
}

template<typename T>
int L_arr<T>::search_first(function<bool(T)> f)
{
	for (int i = 0; i < count; i++)
	{
		if (f(data[i])) return i;
	}
	return -1;
}