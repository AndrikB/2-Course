#pragma once
template<typename T>
class L_CL
{
public:
	virtual bool add_L(T d)=0;
	virtual int size() = 0;
	virtual void del_all_L() = 0;
	virtual	void del_i_L(int k) = 0;
	virtual	int search_el(T d) = 0;
	virtual	T search_i_el(int k) = 0;

/*
	 void push_back(T a) = 0;
	 void push_front(T a) = 0;
	 void pop_back() = 0;
	 void pop_front() = 0;
	 void show() = 0;
	virtual bool is_empty() = 0;
	virtual T back() = 0;
	virtual T front() = 0;
	virtual bool erase_from_position(int position) = 0;
	virtual bool delete_data(T a) = 0;
	virtual int size() const = 0;
	virtual void clear() = 0;
	virtual T operator[](int index) = 0;
	virtual void sort() = 0;*/
};