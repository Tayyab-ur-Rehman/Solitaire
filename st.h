#pragma once
#include<iostream>
using namespace std;
template <typename T >
class MyStack
{
public:

	T* ptr;
	int size;
	int capacity;
	int hidden;

	MyStack()
	{
		hidden = 0;
		size = 0; capacity = 1;
		ptr = new T[capacity];
	}
	MyStack(int cap, int h = 0)
	{
		this->capacity = cap;
		this->hidden = h;
		this->size = 0;
		ptr = new T[capacity];
	}
	/*MyStack(const MyStack& a)
	{
		this->capacity =a.capacity ;
		this->size = a.size;
		this->hidden = a.hidden;
		this->ptr = new T[capacity];

		for (int i = 0; i < a.size; i++)
		{
			T val = a.ptr[i];
			this->push(val);
		}
	}
	/*
	MyStack operator =(const  MyStack<T> &a)
	{
		return MyStack(a);
	}*/
	void push(T a)
	{
		if (size == capacity)
		{
			capacity *= 2;
			T* ptr2 = new T[capacity];
			for (int i = 0; i < size; i++)
			{
				ptr2[i] = ptr[i];
			}
			delete[] ptr;
			ptr = ptr2;
			ptr[size] = a;
			size++;
		}
		else
		{
			ptr[size] = a; size++;
		}

	}
	void pop()
	{
		this->size--;
	}
	T top()
	{
		if (size != 0)
		{
			return this->ptr[size - 1];
		}
		else
			return T();
	}
	int size_()
	{

		return this->size;
	}
	T  & operator[](int i)
	{
		if (i >= hidden && i < size)
			return ptr[i];
		return T();
	}
	T  index(int i)
	{
		if (i > hidden && i < size)
			return ptr[i];
		return T();
	}
};











#pragma once
