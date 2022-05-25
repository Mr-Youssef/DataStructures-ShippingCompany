#pragma once
#include <iostream>

class Truck
{
private:
	int truckID;
	char truckType;
	int truckCapacity;
	int checkupDuration;
	int speed;
	int deliveryInterval;
	int assignedCargoCount;  //No. of cargos assigned in the truck and still are being delivered 
	int JnumForCheckup; //No. of journeys before checkup taken from input file), if this no. is reached the truck will go to checkup
	int journeyCount; //No. of done journeys that will be used for the maintenance (checkup) time
	bool inMaintenance;
public:
	Truck(char type, int s, int capacity, int numBeforeChkup, int chkupDuration);
	void setTruckID(int);
	int getTruckID();

	void setTruckType(char);
	char getTruckType();

	void setTruckCapacity(int);
	int getTruckCapacity();

	void setCheckupDuration(int);
	int getCheckupDuration();

	void setSpeed(int);
	int getSpeed();

	void setDeliveryInterval(int);
	int getDeliveryInterval();

	void incrementCargoCount();
	int getCargoCount();

	void setJNumForCheck(int);
	int getJNumForCheck();

	void incrementJourneyCount();
	int getJourneyCount();
	~Truck();
};
