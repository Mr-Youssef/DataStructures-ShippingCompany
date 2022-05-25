#include "Truck.h"

Truck::Truck(char type, int s, int capacity, int numBeforeChkup, int chkupDuration)
{
	truckID = -1; 
	truckType = type;
	truckCapacity = capacity;
	checkupDuration = chkupDuration;
	speed = s;
	deliveryInterval = 0;
	assignedCargoCount = 0;
	JnumForCheckup = numBeforeChkup;
	journeyCount = 0;
	inMaintenance = false;
}
void Truck::setTruckID(int id)
{
	truckID = id;
}
int Truck::getTruckID()
{
	return truckID;
}
void Truck::setTruckType(char type)
{
	truckType = type;
}
char Truck::getTruckType()
{
	return truckType;
}
void Truck::setTruckCapacity(int c)
{
	truckCapacity = c;
}
int Truck::getTruckCapacity()
{
	return truckCapacity;
}
void Truck::setCheckupDuration(int dur)
{
	checkupDuration = dur;
}
int Truck::getCheckupDuration()
{
	return checkupDuration;
}
void Truck::setSpeed(int sp)
{
	speed = sp;
}
int Truck::getSpeed()
{
	return speed;
}
void Truck::setDeliveryInterval(int DI)
{
	deliveryInterval = DI;
}
int Truck::getDeliveryInterval()
{
	return deliveryInterval;
}
void Truck::incrementCargoCount()
{
	assignedCargoCount++;
}
int Truck::getCargoCount()
{
	return assignedCargoCount;
}
void Truck::setJNumForCheck(int j)
{
	JnumForCheckup = j;
}
int Truck::getJNumForCheck()
{
	return JnumForCheckup;
}
void Truck::incrementJourneyCount()
{
	journeyCount++;
}
int Truck::getJourneyCount()
{
	return journeyCount;
}
Truck::~Truck()
{
}