#pragma once
#include <iostream>

template<typename T>
class Node
{
private:
	T* data;	// A data item (can be any complex structure), the use of pointer is for reducing memory size
	Node<T>* next;	// Pointer to next node
	int priority;  //For the priorityQ, largest priority value is the highest priority 
public:

	Node() //default constructor
	{
		next = nullptr;
	}

	//Node(T* newItem) //non-default constructor
	//{
	//	data = newItem;
	//	next = nullptr;
	//}

	Node(T* newItem, int pr= -1) //non-default constructor
	{
		data = newItem;
		next = nullptr;
		priority = pr;
	}

	void setData(T* newItem)  //Must overload "=" 
	{
		data = newItem;
	} 

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} 
	void setPriority(int pr)
	{
		priority = pr;
	}
	
	T* getData() const
	{
		return data;
	} 

	Node<T>* getNext() const
	{
		return next;
	}
	int getPriority()
	{
		return priority;
	}
};