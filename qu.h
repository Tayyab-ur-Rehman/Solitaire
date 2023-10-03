#pragma once
#include<iostream>
using namespace std;


class card
{
public:
	char colour;// r,b
	char type;//h,c,d,s
	int card_num;//1 2 3 4 5 6 7 8 9 10 J Q K
	int slot_num()
	{
		char a = this->type;
		if (a == 'd')
			return 0;
		if (a == 'c')
			return 1;
		if (a == 'h')
			return 2;
		if (a == 's')
			return 3;
	}
};
template <typename T >
class TQueue
{
public:
	T* ptr;
	int size;
	int capacity; int fi, ri;
	int hidden = 0;
	TQueue(int cap, int hid = 0)
	{
		capacity = cap;
		size = ri = fi = 0;
		hidden = hid;
		ptr = new T[capacity];
	}
	TQueue()
	{
		capacity = 25;
		size = ri = fi = 0;
		ptr = new T[capacity];

	}
	/*TQueue(const TQueue <T>& a)
	{
		this->hidden = a.hidden;
		this->size = a.size;
		this->capacity = a.capacity;

		this->ptr = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = a.ptr[i];
		}
		this->fi = a.fi;
		this->ri = a.ri;

	}*/
	/*TQueue operator = (TQueue <T> a)
	{
		return TQueue(a);
	}*/
	int size_()
	{
		return this->size;
	}
	bool is_full()
	{
		if (size == capacity)
			return true;
		return false;

	}
	bool is_empty()
	{
		if (size == 0)
			return true;
		return false;

	}
	void Dequeue()
	{
		if (size != 0) {
			fi = (fi + 1) % capacity;
			size--;
		}
	}
	void Enqueue(T val)
	{
		if (size == capacity)
		{
			T* ptr2 = new T[capacity * 2];
			for (int i = 0; i < size; i++)
			{

				ptr2[i] = ptr[(fi + i) % size];
			}
			delete[] ptr; ptr = ptr2;
			ptr[size] = val;

			capacity *= 2; fi = 0;
			ri = size - 1;
		}
		else
		{
			//cout << "\nval assigned\n";
			ptr[ri] = val;
			ri = (ri + 1) % capacity;

		}
		size++;
	}
	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << ptr[(i + fi) % capacity] << " ";
		}
		cout << endl;
	}
	T Front() const
	{
		return ptr[fi];
	}
	T operator [](int i)
	{
		return ptr[(i + fi) % capacity];
	}
	T index(int i)
	{
		return ptr[(i + fi) % capacity];
	}
};

