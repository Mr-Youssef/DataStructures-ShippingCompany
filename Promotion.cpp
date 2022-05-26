#include <iostream>
#include "Promotion.h"

Promotion::Promotion(int ID, int ED, int EH, char CT, int RD, int RH, int LT, int DD, int CC, int EX) :Event(ID, ED, EH)
{
	cargoType = CT;
	readyDay = RD;
	readyHour = RH;
	loadTime = LT;
	deliveryDistance = DD;
	cargoCost = CC;
	extraM = EX;
}

void Promotion::Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr)
{
	Cargo* cargoToBePromoted = new Cargo(CargoID, readyDay, readyHour, loadTime, deliveryDistance, cargoCost, 'N');
	Node<Cargo>* nodeToBePromoted = new Node<Cargo>(cargoToBePromoted);
	Cargo* data = nodeToBePromoted->getData();
	int found = normalCargo.getIndexOf(*data);
	if (found != -1)
	{
		//Cargo* Temp = nodeToBePromoted->getData();
		Cargo* promote = new Cargo(CargoID, data->GetReadyDay(), data->GetReadyHour(), loadTime, deliveryDistance, cargoCost + extraM, 'V');
		/*Priority Equation*/
		int readyTime = promote->GetReadyHour() + promote->GetReadyDay();
		int priority = (readyTime * promote->GetDeliveryDistance() * promote->GetCargoCost()) / (readyTime + promote->GetDeliveryDistance() + promote->GetCargoCost());
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