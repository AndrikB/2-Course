#pragma once
#include<thread>
using std::function;

enum MODE
{
	arr,
	list,
	Vector
};

template<typename T>
class L_CL
{
public:
	virtual bool add_tail(T d)=0;
	virtual bool add_head(T d) = 0;
	virtual int size() = 0;
	virtual void clean() = 0;
	virtual	void del_i(int k) = 0;
	virtual	int search_el(T d) = 0;
	virtual	T search_by_index(int k) = 0;
	virtual int search_first_with (function<bool(T)> f) = 0;
	
};