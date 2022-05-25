#pragma once
#include"Node.h"
//General Linked List
template<class T>
class List
{
	Node<T>* Head;	//pointer points to the first node in the list
	Node<T>* Tail;	//pointer points to the last node in the list
	int count;		//current count of list item
	Node<T>* getNodeAt(int) const;//get pointer which refers to this position

public:
	List();
	List(const List<T>&); //copy constructor
	Node<T>* getHead();
	bool isEmpty()const;
	int getLength()const;
	T* getEntry(int)const;
	bool insert(const int, T*);
	void InsertEnd(T*);
	bool remove(int);
	void clear();
	int getIndexOf(const T&)const; //Needed in the cancellation event class
	Node<T>* getPointerTo(const T&)const;
	virtual ~List();  //Destructor should be virtual
};

template<class T>
List<T>::List()
{
	Head = nullptr;
	Tail = nullptr;
	count = 0;
}

/*Copy Constructor*/
template<class T>
List<T>::List(const List<T>& L2)
{
	count = L2.count;
	Head = Tail = nullptr;
	Node<T>* originalptr = L2.Head;
	if (originalptr == nullptr)
		Head = nullptr;  //original list is empty so is the copy
	int i = 1;
	while (originalptr)
	{
		this->insert(i, originalptr->getData());
		originalptr = originalptr->getNext();
		i++;
	}
}

template<class T>
Node<T>* List<T>::getNodeAt(int position)const
{
	Node<T>* temp = Head;
	if (count < position || position <= 0)  //position <=0 bec in the general list we start by position 1 not 0 as usual
	{
		return nullptr;
	}
	else
	{
		for (int i = 1; i < position; i++)
			temp = temp->getNext();
		return temp;
	}
}

template<class T>
Node<T>* List<T>::getHead()
{
	return this->Head;
}

template<class T>
bool List<T>::isEmpty()const
{
	if (Head == nullptr)
		return true;
	else
		return false;
}

template<class T>
int List<T>::getLength()const
{
	return count;
}

template<class T>
T* List<T>::getEntry(int pos)const
{
	Node<T>* target = getNodeAt(pos);
	if (target)
		return target->getData();
	return(NULL);
}

/*send as parameter the position to insert in & the variable to insert in that position*/
/*item is sent by pointer instead of const T& bec it is needed as a pointer in the preparation 
event class due to dynamic allocation*/
template<class T>
bool List<T>::insert(int index, T* item)
{
	if (count + 1 < index || index <= 0)
		return false;
	Node<T>* newNode = new Node<T>(item);
	if (index == 1)
	{
		newNode->setNext(Head);
		Head = newNode;
		if (count == 0)  //if this is the first node to insert (list was empty)
		{
			Tail = newNode;
		}
	}
	else if (index == count + 1) //inserting in the last node (after the tail not in the tail node)
	{
		Tail->setNext(newNode);
		Tail = newNode;
	}
	else
	{
		Node<T>* temp = getNodeAt(index - 1);
		if (temp->getNext() == Tail)  //if we want to insert in the tail node
		{
			temp->setNext(newNode);
			newNode->setNext(Tail);
			return true;
		}
		newNode->setNext(temp->getNext());
		temp->setNext(newNode);
	}
	count++;
	return true;
}

template<class T>
void List<T>::InsertEnd(T* data)
{
	Node<T>* ptrTemp = new Node<T>(data);
	if (!Head)
	{
		Head = ptrTemp;
		count++;
		return;
	}
	Node<T>* p = Head;
	while (p->getNext())
		p = p->getNext();
	p->setNext(ptrTemp);
	count++;
}

template<class T>
bool List<T>::remove(int pos)
{
	if (isEmpty())
		return false;
	Node<T>* temp = getNodeAt(pos);
	if (temp)
	{
		Node<T>* target = Head;  //target is used as a previous ptr to the node which will be deleted (prev to temp) 
		if (temp == Head)
		{
			Head = Head->getNext();
			delete temp;
		}
		else if (temp == Tail)
		{
			while (target->getNext() != Tail)
			{
				target = target->getNext();
			}
			Tail = target;
			Tail->setNext(nullptr);
			delete temp;
		}
		else
		{
			while (target->getNext() != temp)
			{
				target = target->getNext();
			}
			target->setNext(temp->getNext());
			delete temp;
		}
		count--;
		return true;
	}
	return false;
}

template<class T>
void List<T>::clear()
{
	if (!isEmpty())
	{
		while (Head)
		{
			Node<T>* temp = Head;
			Head = Head->getNext();
			delete temp;
		}
		count = 0;
	} 
	//OR simply call remove(1) but to reduce function call headache we didn't use it
}

template<class T>
int List<T>::getIndexOf(const T& target)const
{
	bool found = false;
	Node<T>* targetPtr = Head;
	int position = -1;  //returns -1 if not found or if list is empty
	int count = 1;
	while (!found && targetPtr)
	{
		if (*targetPtr->getData() == target)
		{
			found = true;
			position = count;
		}
		else
			targetPtr = targetPtr->getNext();
		count++;
	}
	return position;
}

template<class T>
Node<T>* List<T>::getPointerTo(const T& target)const
{
	bool found = false;
	Node<T>* curPtr = Head;
	while (!found && curPtr)
	{
		if (curPtr->getData() == target)
			found = true;
		else
			curPtr = curPtr->getNext();
	}
	return curPtr;
}

template<class T>
List<T>::~List()
{
	clear();
}