#pragma once

#include <cstddef>


class CVectorInt
{
public:
	CVectorInt(int);
	~CVectorInt();
	/*
       Requests that the vector capacity be at least enough to contain n elements.
	   If n is greater than the current vector capacity, 
	   the function causes the container to reallocate its storage increasing its capacity to n
	*/
	void reserve(int);
	//Returns the number of int elements allocated
	int capacity();
	//Returns the number of elements actually inserted
	int size();
	//Returns ture if the vector empty
	bool empty();
	//frees all the data and resets the size
	void clear();
	//adds an int elements at the end
	void push_back(int);
	//removes an int elements at the end and return it
	int pop_back();
	//removes an int elements at specific index
	void remove(int);

	//Overload operator [] to access the data at a specific index
	int& operator[](std::size_t idx) { return arr[idx]; }
	const int& operator[](std::size_t idx) const { return arr[idx]; }

protected:
private:
	int *arr;
	int index;
	int base_length;
	int expend_length;
	// If the vector is full doubles its size
	void shrink();
	// If the vector is half empty halves its size
	void expand();
}; 
