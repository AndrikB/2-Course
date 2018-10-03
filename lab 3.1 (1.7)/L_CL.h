#pragma once
#include<thread>
#include<utility>

using std::function;

enum MODE
{
	array,
	list,
	vector
};

template<typename T1>
class Node
{
public:
	Node<T1> * next;
	T1 data;

};
template<typename T>
struct ptr
{
	Node<T>*head = nullptr;
	T* data;
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
	virtual int search_first_with (function<bool(T)> f) = 0;
	virtual T& operator[](int k) = 0;
	virtual bool rewrite(int k, T d) = 0;
	virtual ptr<T> begin() = 0;
};
