#pragma once

#include "L_CL_arr.h"
#include "L_CL_list.h"
#include "L_CL_vector.h"

#include "L_CL.h"

#include<thread>

using std::function;


template<typename T>
class List :public L_CL<T>
{
public:
	List() { impl = new L_arr<T>; }
	List(int size) 
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
	T search_by_index(int i);
	int search_first_with (function<bool(T)> f);

private:
	MODE mode = arr;
	int SIZE = 0;
	L_CL<T>*impl;
};

template<typename T>
void List<T>::set_mode(int mode)
{
	delete impl;

	if (mode == 1)
	{
		if (SIZE > 0)
			impl = new L_arr<T>(SIZE);
		else
			impl = new L_arr<T>;
		this->mode = MODE::arr;
		
	}
	else if (mode == 2)
	{
		impl = new L_list<T>;
		this->mode = MODE::list;
	}
	else 
	{
		impl = new L_vector<T>;
		this->mode = MODE::Vector;
	}
}

template<typename T>
bool List<T>::add_tail(T d)
{
	return impl->add_tail(d);
}

template<typename T>
bool List<T>::add_head(T d)
{
	return impl->add_head(d);
}

template<typename T>
int List<T>::size()
{
	return impl->size();
}

template<typename T>
void List<T>::clean()
{
	impl->clean();
}

template<typename T>
void List<T>::del_i(int k)
{
	impl->del_i(k);
}

template<typename T>
int List<T>::search_el(T d)
{
	return impl->search_el(d);
}

template<typename T>
T List<T>::search_by_index(int i)
{
	return impl->search_by_index(i);
}

template<typename T>
int  List<T>::search_first_with (function<bool(T)> f)
{
	return impl->search_first_with (f);
}

