#pragma once
#include "Event.h"

class Cancellation : public Event
{
private:

public:
	Cancellation(int CargoID, int EventDay, int EventHour);
	virtual void Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr);
	~Cancellation();
};