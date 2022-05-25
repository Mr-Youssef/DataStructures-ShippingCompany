#pragma once
#include<iostream>
#include "Cargo.h"
#include "Truck.h"
#include "LinkedList.h"
#include "Queue.h"
#include "PriorityQ.h"
#include "Event.h"

class Event {

protected:
	int EventDay;  //Event time in days
	int EventHour;
	int CargoID;

public:
	Event(int CargoID, int EventD, int EventH);

	void SetEventDay(int EventD);

	int GetEventDay();

	void SetEventHour(int EventH);

	int GetEventHour();
	
	void SetCargoID(int CargoID);

	int GetCargoID();

	///*execute to create mission and add it to the appropriate list*///
	virtual void Execute(List<Cargo>& normalCargo, Queue<Cargo>& specialCargo, PriorityQ<Cargo>& vipCargo, int* arr) = 0;

	~Event();

};