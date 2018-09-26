#pragma once
#include "L_LC.h"
#include<thread>
using std::function;
template<typename T>
class L_list :public L_CL<T>
{
public:
	//конструктори
	L_list() { Size = 0; /*el_n = */head = tail = nullptr; }

	//спільні
	bool add_L(T d);
	int size();
	void del_all_L();
	void del_i_L(int k);
	int search_el(T d);
	T search_i_el(int k);
	int search_first(function<bool(T)> f);

	//деструктор
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
	template<typename T>
	class Node
	{
	public:
		Node * next;
		T data;
				
	};

	int count;//к-ть елементів зара
	//Node<T> *el_n;//в даний момент часу
	Node<T> *head;//голова
	Node<T> *tail;//хвіст
	
};

template<typename T>
bool L_list<T>::add_L(T d)
{
	count++;
	if (!head) 
	{
		head = new Node;
		tail = head;
		tail->data = d;
		tail->next = tail;
		//el_n = head;
		return true;
	}
	else
	{
		tail->next = new Node;
		tail = tail->next;
		tail->data = d;
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
void L_list<T>::del_all_L()
{
	tail->next = nullptr;
	while (head->next) 
	{
		tail = head;
		head = head->next;
		delete &tail;
	}
}

template<typename T>
void L_list<T>::del_i_L(int k)
{
	Node<T> *tmp = head;
	if (k >= size || k < 0) return;
	size--;
	if (k == 0)
	{
		head = head->next;
		delete &tmp;
		return;
	}
	for (int i = 1; i < k; i++)
	{
		tmp = tmp->next;
		Node<T> *tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		delete &tmp2;
	}
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
		if (j > size) return -1;
		j++;
	}
	return -1;
}

template<typename T>
T L_list<T>::search_i_el(int k)
{
	Node<T> *tmp = head;
	if (k >= size || k < 0) return nullptr;
	for (int i = 1; i < k; i++)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}

template<typename T>
int L_list<T>::search_first(function<bool(T)> f)
{
	Node<T> *tmp = head;
	for (int i = 0; i < count; i++)
	{

		if (f(tmp->data)) return i;
	}
	return -1;
}