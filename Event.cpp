#include "Event.h"

Event::Event(int cargoId, int eventD, int eventH) 
{
	CargoID = cargoId;
	EventDay = eventD;
	EventHour = eventH;
}

void Event::SetEventDay(int eventD) { EventDay = eventD; }

int Event::GetEventDay() { return EventDay; }

void Event::SetEventHour(int eventH) { EventHour = eventH; }

int Event::GetEventHour() { return EventHour; }

void Event::SetCargoID(int cargoID) { CargoID = cargoID; }

int Event::GetCargoID() { return CargoID; }

Event::~Event() {}