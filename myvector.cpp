#include <iostream>
#include "contact.h"
#include "myvector.h"
#include <stdexcept>

using namespace std;


template <typename T>
MyVector<T>::MyVector()//No argument constructor
{
	v_capacity = 1;//initially the capacity is one
	data = new T[v_capacity];
	v_size = 0;
}

template <typename T>
MyVector<T>::~MyVector()//Destructor
{
	delete [] data;//deleting the dynamically creted array
}

template <typename T>
void MyVector<T>::push_back(T element)//Add an element at the end of vector
{
	if (v_size == v_capacity)
	{
		T* A = new T[v_capacity*2]; // resize the array
		for (int j = 0; j < v_size; j++) // copy contents to new array
		A[j] = data[j];
		if (data != NULL) delete [] data; // discard old array
		data = A; // make A the new array
		v_capacity = v_capacity*2; // set new capacity
	}
	
	data[v_size] = element; // put “element” at index the back
	v_size++; 
}

template <typename T>
void MyVector<T>::insert(int index, T element)//Add an element at the index 
{
	if (v_size == v_capacity)
	{
		T* A = new T[v_capacity*2]; // resize the array
		for (int j = 0; j < v_size; j++) // copy contents to new array
		A[j] = data[j];
		if (data != NULL) delete [] data; // discard old array
		data = A; // make A the new array
		v_capacity = v_capacity*2; // set new capacity
	}

	if (index < 0||index > v_size-1)//checks the validation of the index
		throw runtime_error("illegal index"); 

	for (int j = v_size-1; j >= index; j--) // shift elements up
		data[j+1] = data[j];
	data[index] = element; // put “element” at "index"
	v_size++; 
}

template <typename T>
T MyVector<T>::erase(int index)//Removes an element from the index
{
	T deletedElem;
	if (index < 0||index > v_size-1)//checks the validation of the index
		throw runtime_error("illegal index"); 

	deletedElem = data[index];
	for (int j = index; j+1 < v_size; j++) // shift elements up
		data[j] = data[j+1];
	v_size--;
	return(deletedElem);
}

template <typename T>
T& MyVector<T>::operator[](int index)//return reference of the element at index
{
	return data[index]; //returns the element at the index
}

template <typename T>
T& MyVector<T>::at(int index)//return reference of the element at index
{

	if (index < 0||index > v_size-1)//checks the validation of the index
		throw runtime_error("illegal index"); 
	for(int i=0; i<v_size; i++)//iterates over the vector to find the element
	{
		if(i==index)
		{
			return(data[i]);//returns the data at index
		}
	}
	return data[0];
}

template <typename T>
const T& MyVector<T>::front()//Returns reference of the first element in the vector
{
	return(data[0]);//returns the first element
}

template <typename T>
int MyVector<T>::size() const//Return current size of vector
{
	return(v_size);//returns the size of the vector
}

template <typename T>
int MyVector<T>::capacity() const//Return capacity of vector
{
	return(v_capacity);//returns te total capacity including the empty spacs
}

template <typename T>
bool MyVector<T>::empty() const//Rturn true if the vector is empty, False otherwise
{
	return(v_size==0);
}

template <typename T>
void MyVector<T>::display() //helps to print all the contact informations inside the vector
{
	cout << v_size <<" records found:" << endl;
	for (int i = 0; i < v_size; i++)
	{
		cout << i+1 <<". ";
		data[i].print();
	}
}

template class MyVector<Contact>;
