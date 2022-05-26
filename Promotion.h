#pragma once
#include "Event.h"

class Promotion : public Event
{
private:
	char cargoType;
	int readyDay;
	int readyHour;
	int loadTime;
	int deliveryDistance;
	int cargoCost;
	int extraM;
public:
	Promotion(int CargoID, int EventDay, int EventHour, char CT, int RD, int RH, int LT, int DD, int CC, int EX);
	virtual void Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr);
	~Promotion();
};