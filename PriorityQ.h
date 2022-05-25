#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class PriorityQ
{
private:
	Node<T>* front;

public:
	//Constructor
	PriorityQ()
	{
		front = nullptr; 
	}
	//Function that enqueues the elemtents sorted according to the key
	bool enqueue(T* newEntry, const int& newPr)
	{
		//Creating the new node to be inserted 
		Node<T>* newNodePtr = new Node<T>(newEntry, newPr);
		//If the entry is in the first place (the list is empty) OR the priority of the newNodePtr is the highest set it in the front
		if (isEmpty() || newNodePtr->getPriority() > front->getPriority())
		{
			newNodePtr->setNext(front);
			front = newNodePtr;
		}
		else
		{
			Node<T>* temp = front;
			while (temp->getNext() && temp->getNext()->getPriority() >= newNodePtr->getPriority())
				temp = temp->getNext();

			newNodePtr->setNext(temp->getNext());
			temp->setNext(newNodePtr);
			
		}
		return true;
	}

	//Function the takes out elements out of the queue
	bool dequeue(Node<T>*& frntEntry)
	{
		if (isEmpty())
			return false;
		Node<T>* nodeToDeletePtr = front;
		T* tempp;
		tempp = front->getData();
		frntEntry = new Node<T>(tempp);
		front = front->getNext();
		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		return true;
	}

	//Function the checks the first element.
	bool peek(Node<T>*& frntEntry) const
	{
		if (isEmpty())
			return false;
		frntEntry = front->getData();
		return true;
	}

	//Function that checks whether the queue is empty or not
	bool isEmpty()
	{
		return (front == nullptr);
	}

	int getSize()
	{
		Node<T>* NodePtr = front;
		int size = 0;
		while (NodePtr) {
			size++;
			NodePtr = NodePtr->getNext();
		}
		return size;
	}

	//~PriorityQ()
	//{
	//	T temp;
	//	//Free (Dequeue) all nodes in the queue
	//	while (dequeue(temp));
	//}
};