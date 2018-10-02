#pragma once
#include<utility>
#include"L_CL_list.h"

template<typename T>
class iter
{
public:
	
	iter(ptr<T> tmp)
	{
		this->pointer = tmp;
	}
	T& operator*();
	void operator++();
	void operator++(int a);
	void operator+=(int a);
	void operator=(ptr<T> p);
private:
	ptr<T> pointer;
	ptr<T> head;
};
template<typename T>
T& iter<T>::operator*()
{
	return *pointer.data;
}
template<typename T>
void iter<T>::operator=(ptr<T> pointer)
{
	this->pointer = pointer;
}
template<typename T>
void iter<T>::operator++()
{
	if (!pointer.head)
		pointer.data++;
	else
	{
		pointer.head = pointer.head->next;
		pointer.data = &pointer.head->data;
	}
}

template<typename T>
void iter<T>::operator++(int a)
{

	if (!pointer.head)
		pointer.data++;
	else
	{
		pointer.head = pointer.head->next;
		pointer.data = &pointer.head->data;
	}
}

template<typename T>
void iter<T>::operator+=(int a)
{

	if (!pointer.head)
		pointer.data+=a;
	else 
		for (int i=0;i<a;i++)
		{
			pointer.head = pointer.head->next;
			pointer.data = &pointer.head->data;
		}
			
}