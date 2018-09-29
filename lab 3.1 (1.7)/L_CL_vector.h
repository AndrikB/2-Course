#pragma once
#include "L_CL.h"
#include <vector>
#include<thread>
using std::function;
using std::vector;

template<typename T>
class L_vector :public L_CL<T>
{
public:
	//конструктори
	

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

	/////////////////
private:
	vector<T> data;

};

template<typename T>
bool L_vector<T>::add_tail(T d) 
{
	data.push_back(d);
	return true;
}

template<typename T>
bool L_vector<T>::add_head(T d)
{
	data.insert(data.begin(), d);
	return true;
}

template<typename T>
int L_vector<T>::size()
{
	return (int) data.size();
}

template<typename T>
void L_vector<T>::clean()
{
	data.clear();
}

template<typename T>
void L_vector<T>::del_i(int k)
{
	data.erase(data.begin() + k);
}

template<typename T>
int  L_vector<T>::search_el(T d)
{
	int s = (int) data.size();
	for (int i = 0; i < s; i++)
	{
		if (d == data[i])
			return i;
	}
	return -1;
}

template<typename T>
T L_vector<T>::search_by_index(int k)
{
	if (k < data.size()&&k >= 0) return data[k];
	return (T) nullptr;
}

template<typename T>
int L_vector<T>::search_first_with (function<bool(T)> f)
{
	for (int i = 0; i < size(); i++)
	{
		if (f(data[i])) return i;
	}
	return -1;
}