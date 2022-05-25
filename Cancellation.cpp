#include <iostream>
#include "Cancellation.h"

Cancellation::Cancellation(int ID, int ED, int EH) :Event(ID, ED, EH)
{

}

void Cancellation::Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr)
{
	bool removed = false;
	Cargo* cargoToBeCancelled = new Cargo(CargoID, -1, -1, -1, -1, 'N'); //create a pointer to a cargo & give it the id you want to delete
	/*Bec Linked list consists of nodes not cargos, so insert the cargo in a node to be able to delete it in the L.List*/
	Node<Cargo>* nodeToBeDeleted = new Node<Cargo>(cargoToBeCancelled); 
	Cargo* data = nodeToBeDeleted->getData();
	int position = normalCargo.getIndexOf(*data); //search for the cargo in the list that has the same id for the dynamically allocated cargo 
	removed = normalCargo.remove(position);  //then remove it from the list
	if (removed)  //if found decrement the count of the normal cargos 
		arr[0]--;
	delete cargoToBeCancelled;
	delete nodeToBeDeleted;
}

Cancellation::~Cancellation()
{

}