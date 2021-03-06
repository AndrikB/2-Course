#pragma once
#include "L_CL.h"
#include<thread>
#include<vector>
using std::vector;
using std::function;



template<typename T>
class L_list :public L_CL<T>
{
public:

	L_list() { count = 0; head = tail = nullptr; }


	bool add_tail(T d)override;
	bool add_head(T d)override;
	int size()override;
	void clean()override;
	void del_i(int k)override;
	int search_el(T d)override;
	int search_first_with (function<bool(T)> f) override;
	T& operator[](int i)override;
	bool rewrite(int i, T d)override;
	ptr<T> begin()override;



	~L_list() {
		tail->next = nullptr;
		while (head->next)
		{
			tail = head;
			head = head->next;
			delete &tail;
		}
		delete tail;
		delete head;
	}
private:
	

	int count;//�-�� �������� ����

	Node<T> *head;//������
	Node<T> *tail;//����
};

template<typename T>
ptr<T> L_list<T>::begin()
{
	ptr<T> tmp;
	tmp.data = &head->data;
	tmp.head = head;
	return tmp;
}

template<typename T>
bool L_list<T>::add_tail(T d)
{
	count++;
	if (!head) 
	{
		head = new Node<T>;
		tail = head;
		tail->data = d;
		tail->next = tail;
		return true;
	}
	else
	{
		tail->next = new Node<T>;
		tail = tail->next;
		tail->data = d;
		tail->next = head;
		return true;
	}
	
}

template<typename T>
bool L_list<T>::add_head(T d)
{
	count++;
	if (!head)
	{
		head = new Node<T>;
		tail = head;
		tail->data = d;
		tail->next = tail;
		return true;
	}
	else
	{
		Node<T> *tmp = new Node<T>;
		tmp->next = head;
		tmp->data = d;
		head = tmp;
		tail->next = head;
		return true;
	}


}

template<typename T>
int L_list<T>::size()
{
	return count;
}

template<typename T>
void L_list<T>::clean()
{
	tail->next = nullptr;
	while (head->next) 
	{
		tail = head;
		head = head->next;
		delete tail;
	}
	count = 0;
	delete head;
	head = tail = nullptr;
}

template<typename T>
void L_list<T>::del_i(int k)
{
	Node<T> *tmp = head;
	if (k >= count || k < 0) return;
	count--;
	if (k == 0)
	{
		head = head->next;
		delete tmp;
		return;
	}
	for (int i = 1; i < k; i++)
	tmp = tmp->next;
	Node<T> *tmp2 = tmp->next;
	tmp->next = tmp->next->next;
	delete tmp2;
	
}

template<typename T>
int L_list<T>::search_el(T d)
{
	int j = 0;
	Node<T> *tmp = head;
	while (tmp)
	{
		if (tmp->data == d) return j;
		tmp = tmp->next;
		if (j > count) return -1;
		j++;
	}
	return -1;
}

template<typename T>
T& L_list<T>::operator[](int k)
{
	Node<T> *tmp = head;
	if (k >= count || k < 0)exit(1);
	for (int i = 0; i < k; i++)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}

template<typename T>
int L_list<T>::search_first_with (function<bool(T)> f)
{
	Node<T> *tmp = head;
	for (int i = 0; i < count; i++)
	{

		if (f(tmp->data)) return i;
		tmp = tmp->next;
	}
	return -1;
}

template<typename T>
bool L_list<T>::rewrite(int k, T d)
{
	if (k >= count || k < 0) return false;
	Node<T> *tmp = head;
	while (k)
	{
		k--;
		tmp = tmp->next;
	}
	tmp->data = d;
	return true;
}