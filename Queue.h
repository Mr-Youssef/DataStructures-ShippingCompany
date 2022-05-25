#pragma once
#include<iostream>
#include "Node.h"
using namespace std;

template <typename T>
class Queue
{
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	Queue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}
	bool enqueue(T* newEntry)
	{
		Node<T>* newPtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
		{
			frontPtr = newPtr; // The queue is empty
			backPtr = frontPtr;
		}
		else
			backPtr->setNext(newPtr); // The queue was not empty
		backPtr = newPtr; // New node is the last node now
		return true;
	}
	bool dequeue(Node<T>*& frntEntry)
	{
		if (isEmpty())
			return false;
		Node<T>* nodeToDeletePtr = frontPtr;
		T* tempp;
		tempp = frontPtr->getData();
		frntEntry = new Node<T>(tempp);
		frontPtr = frontPtr->getNext();
		if (nodeToDeletePtr == backPtr)     // Special case: last node in the queue
			backPtr = nullptr;
		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		return true;
	}

	bool peek(Node<T>*& frntEntry)
	{
		if (isEmpty())
			return false;
		T* tempp;
		tempp = frontPtr->getData();
		frntEntry = new Node<T>(tempp);
		return true;
	}

	bool isEmpty()
	{
		return (this->frontPtr == nullptr);
	}

	int getSize()
	{
		Node<T>* NodePtr = frontPtr;
		int size = 0;
		while (NodePtr) {
			size++;
			NodePtr = NodePtr->getNext();
		}
		return size;
	}
	//~Queue()
	//{
	//	T temp();
	//	//Free (Dequeue) all nodes in the queue
	//	while (dequeue(temp));
	//}
};