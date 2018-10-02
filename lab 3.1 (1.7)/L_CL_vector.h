#pragma once
#include "L_CL.h"
#include <vector>
#include<thread>
using std::function;
using std::vector;
using std::iterator;

//template<typename T>
//class iter_vector:public iter<T>
//{
//public:
//	iter_vector() { i = 0; }
//	void set_head()override;
//
//private:
//	int i;
//};

//template<typename T>
//void iter_vector<T>::set_head()
//{}

template<typename T>
class L_vector :public L_CL<T>
{
public:
	//������������
	

	//������
	bool add_tail(T d)override;
	bool add_head(T d)override;
	int size()override;
	void clean()override;
	void del_i(int k)override;
	int search_el(T d)override;
	//T search_by_index(int k)override;
	int search_first_with (function<bool(T)> f)override;

	T operator[](int i)override;
	bool rewrite(int i, T d)override;

	ptr<T> begin();
	//friend iter_vector set_iter(L_vector L, int i) { iter_vector k(i); return k; }
	
	//����������
	/////////////////
private:

	vector<T> data;
	int iter = 0;

};

template<typename T>
ptr<T> L_vector<T>::begin()
{
	ptr<T> tmp;
	tmp.data = &data[0];
	return tmp;
}

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
	//it = nullptr;
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
T L_vector<T>::operator[](int k)
{
	if (k < data.size()&&k >= 0) return data[k];
	exit(1);
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

template<typename T>
bool L_vector<T>::rewrite(int k, T d)
{
	if (k >= data.size() || k < 0) return false;
	data.erase(data.begin() + k);
	data.insert(data.begin() + k, d);
	return true;
}