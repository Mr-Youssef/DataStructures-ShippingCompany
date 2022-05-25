#pragma once
#include "Event.h"

class Promotion : public Event
{
private:
	char cargoType;
	int readyTime;
	int loadTime;
	int deliveryDistance;
	int cargoCost;
	int extraM;
public:
	Promotion(int CargoID, int EventDay, int EventHour, char CT, int RT, int LT, int DD, int CC, int EX);
	virtual void Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr);
	~Promotion();
};