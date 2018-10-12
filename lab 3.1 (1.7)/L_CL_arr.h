#pragma once
#include "L_CL.h"
#include<thread>
using std::function;


template<typename T>
class L_arr :public L_CL<T>
{
public:

	L_arr();
	L_arr(int length);
	
	bool add_tail(T d)override;
	bool add_head(T d)override;
	int size()override;
	void clean()override;
	void del_i(int k)override;
	int search_el(T d)override;
	int search_first_with (function<bool(T)> f)override;
	T& operator[](int k)override;
	bool rewrite(int k, T d)override;
	ptr<T> begin();
	

	~L_arr() { delete[] data; }

private:
	
	
	T *data = nullptr;
	int count;
	int Max;
};

template<typename T>
ptr<T> L_arr<T>::begin()
{
	ptr<T> tmp;
	tmp.data = &data[0];
	return tmp;
}

template<typename T>
L_arr<T>::L_arr()
{
	Max = 1000;
	count = 0;
	data = new T[Max];
}

template<typename T>
L_arr<T>::L_arr(int length)
{
	Max = length;
	count = 0;
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
	while (count > 0)
	{
		count--;
		
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
T& L_arr<T>::operator[](int k)
{
	if (k < count&&k >= 0) return data[k];
	exit(1);
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

template<typename T>
bool L_arr<T>::rewrite(int k, T d)
{
	if (k < count&&k >= 0) 
	{
		data[k] = d;
		return true;
	}
	return false;
}