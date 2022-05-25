#include <iostream>
#include "Promotion.h"

Promotion::Promotion(int ID, int ED, int EH, char CT, int RT, int LT, int DD, int CC, int EX) :Event(ID, ED, EH)
{
	cargoType = CT;
	readyTime = RT;
	loadTime = LT;
	deliveryDistance = DD;
	cargoCost = CC;
	extraM = EX;
}

void Promotion::Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr)
{
	Cargo* cargoToBePromoted = new Cargo(CargoID, readyTime, loadTime, deliveryDistance, cargoCost, 'N');
	Node<Cargo>* nodeToBePromoted = new Node<Cargo>(cargoToBePromoted);
	Cargo* data = nodeToBePromoted->getData();
	int found = normalCargo.getIndexOf(*data);
	if (found != -1)
	{
		//Cargo* Temp = nodeToBePromoted->getData();
		Cargo* promote = new Cargo(CargoID, data->GetReadyTime(), loadTime, deliveryDistance, cargoCost + extraM, 'V');
		/*Priority Equation*/
		int priority = (promote->GetReadyTime() * promote->GetDeliveryDistance() * promote->GetCargoCost()) / (promote->GetReadyTime() + promote->GetDeliveryDistance() + promote->GetCargoCost());
		vipCargo.enqueue(promote, priority);
		normalCargo.remove(found);
		delete cargoToBePromoted;
		delete nodeToBePromoted;
		arr[0]--;
		arr[2]++;
	}
}

Promotion::~Promotion()
{

}