
#include "CVectorInt.h"
#include <algorithm>
#include <iterator>

CVectorInt::CVectorInt(int size) {
	base_length = size;
	expend_length = base_length;
	arr = new int[size];
}

CVectorInt::~CVectorInt() {
	delete [] arr;
}

void CVectorInt::reserve(int n)
{
	if (capacity() < n) {
		expend_length = n;
		int *temp = arr;
		arr = new int[expend_length];
		for (int i = 0; i < index; i++) {
			arr[i] = temp[i];
		}
		delete[] temp;
	}
}

bool CVectorInt::empty() {
	return index == 0;
}

void CVectorInt::clear()
{
	delete[] arr;
	index = 0;
	expend_length = base_length;
	arr = new int[base_length];
}

int CVectorInt::size() {
	return index;
}

int CVectorInt::capacity() {
	return expend_length;
}

void CVectorInt::push_back(int a) {
	arr[index] = a;
	index++;
	//check if the vector need to be double
	expand();
}

int CVectorInt::pop_back() {
	index--;
	//check if the vector need to be shrink
	shrink();
	return arr[index];
}

void CVectorInt::remove(int i)
{
	// Sheft to the left all items that right from index i
	for (int j = i; i < index; j++) {
		arr[j] = arr[j + 1];
	}
	index--;
	//check if the vector need to be shrink
	shrink();
}

void CVectorInt::shrink() {
	// check if the vector is half empty
	if ((float) size() / capacity() < 0.5) {
		// resize the vector length
		expend_length = std::ceil((float) expend_length / 2);
		// save the pointer to original arr
		int *temp = arr;
		arr = new int[expend_length];
		// copy original arr to new array with the new size
		for (int i = 0; i < index; i++) {
			arr[i] = temp[i];
		}
		// free the original arr
		delete[] temp;
	}
}

void CVectorInt::expand() {
	// check if the vector is full
	if (expend_length == index) {
		// resize the vector length
		expend_length = expend_length * 2;
		// save the pointer to original arr
		int *temp = arr;
		arr = new int[expend_length];
		// copy original arr to new array with the new size
		for (int i = 0; i < index; i++) {
			arr[i] = temp[i];
		}
		// free the original arr
		delete[] temp;
	}
}

