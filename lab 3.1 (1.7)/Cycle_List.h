#pragma once

#include "L_CL_arr.h"
#include "L_CL_list.h"
#include "L_CL_vector.h"

#include "L_CL.h"

#include<thread>
#include <ctime>
#include <cmath>  

using std::function;



template<typename T>
class Cycle_List :public L_CL<T>
{
public:
	Cycle_List() { impl = new L_arr<T>; }
	Cycle_List(int size)
	{
		if (SIZE > 0)
			impl = new L_arr<T>(SIZE);
		else
			impl = new L_arr<T>;
		this->mode = MODE::arr;
	}
	void set_mode(int mode);
	bool add_tail(T d);
	bool add_head(T d);
	int size();
	void clean();
	void del_i(int i);
	int search_el(T d);
	T& operator[](int i);
	int search_first_with(function<bool(T)> f);
	bool rewrite(int i, T d);
	ptr<T> begin();
	bool rand_push(int n = 1, int precision = 0);

private:
	
	int SIZE = 0;
	L_CL<T>*impl;
};

template<typename T>
ptr<T> Cycle_List<T>::begin()
{
	return impl->begin();
}

template<typename T>
void Cycle_List<T>::set_mode(int mode)
{
	delete impl;

	if (mode == 1)
	{
		if (SIZE > 0)
			impl = new L_arr<T>(SIZE);
		else
			impl = new L_arr<T>;
	}
	else if (mode == 2)
		impl = new L_list<T>;

	else
		impl = new L_vector<T>;
}

template<typename T>
bool Cycle_List<T>::add_tail(T d)
{
	return impl->add_tail(d);
}

template<typename T>
bool Cycle_List<T>::add_head(T d)
{
	return impl->add_head(d);
}

template<typename T>
int Cycle_List<T>::size()
{
	return impl->size();
}

template<typename T>
void Cycle_List<T>::clean()
{
	impl->clean();
}

template<typename T>
void Cycle_List<T>::del_i(int k)
{
	impl->del_i(k);
}

template<typename T>
int Cycle_List<T>::search_el(T d)
{
	return impl->search_el(d);
}

template<typename T>
T& Cycle_List<T>::operator[](int i)
{
	return impl->operator[](i%size());
}

template<typename T>
int  Cycle_List<T>::search_first_with(function<bool(T)> f)
{
	return impl->search_first_with(f);
}

template<typename T>
bool Cycle_List<T>::rewrite(int k, T d)
{
	return impl->rewrite(k, d);
}


template<typename T>
inline bool Cycle_List<T>::rand_push(int n, int precision)
{
	return false;
}

template<>
inline bool Cycle_List<int>::rand_push(int n, int precision)
{
	for (int i = 0; i < n; i++)
	{
		int rand_number = rand() % 100;
		if (!impl->add_tail(rand_number)) return false;
	}
	return true;
}

template<>
inline bool Cycle_List<double>::rand_push(int n, int precision)
{
	srand(time(0));
	int num = pow(10, precision);
	for (int i = 0; i < n; i++)
	{
		
		int int_part = rand() % 100;
		int drob_part = rand() % num;
		double a = double(drob_part) / num;//rand drob_part
		double res = double(int_part) + a;
		if (!impl->add_tail(res)) return false;
	}
	return true;
}