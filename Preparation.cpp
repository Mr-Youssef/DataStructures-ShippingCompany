#include "Preparation.h"
Preparation::Preparation(int ID, int ED, int EH, char CT, int RD, int RH, int LT, int DD, int CC):Event(ID,ED,EH)
{
	cargoType = CT;
	readyDay = RD;
	readyHour = RH;
	loadTime = LT;
	deliveryDistance = DD;
	cargoCost = CC;
}

void Preparation::Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr)
{
	if (cargoType == 'N')
	{
		arr[0]++;  //increment number of normal cargos
		Cargo* newNormalCargo = new Cargo(CargoID, readyDay, readyHour, loadTime, deliveryDistance, cargoCost, cargoType);
		normalCargo.InsertEnd(newNormalCargo);
	}
	else if (cargoType == 'S')
	{
		arr[1]++; //increment number of special cargos
		Cargo* newSpecialCargo = new Cargo(CargoID, readyDay, readyHour, loadTime, deliveryDistance, cargoCost, cargoType);
		specialCargo.enqueue(newSpecialCargo);
	}
	else if (cargoType == 'V')
	{
		arr[2]++; //increment number of VIP cargos
		Cargo* newVIPCargo = new Cargo(CargoID, readyDay, readyHour, loadTime, deliveryDistance, cargoCost, cargoType);
		int readyTime = readyDay + readyHour;
		int priority = (readyTime * deliveryDistance * cargoCost) / (readyTime + deliveryDistance + cargoCost);
		vipCargo.enqueue(newVIPCargo, -priority);
	}
}

Preparation :: ~Preparation()
{
}
