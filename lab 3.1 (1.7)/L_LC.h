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

};