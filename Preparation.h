#pragma once
#include "Event.h"
class Preparation : public Event
{
private:
	char cargoType;
	int readyDay;
	int readyHour;
	int loadTime;
	int deliveryDistance;
	int cargoCost;

public:
	Preparation(int cargoID, int eventDay, int eventHour, char cargoType, int readyDay, int readyHour, int loadTime, int deliveryDist, int cargoCost);
	virtual void Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr);
	~Preparation();

};