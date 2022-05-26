#pragma once
#include<iostream>
#include "Truck.h"
using namespace std;

class Cargo
{
private:
	int cargoID;
	int ReadyDay;
	int ReadyHour;
	int loadTime;
	int DeliveryDistance;
	int CargoCost;
	char CargoType;                              ///normal-special-vip
	char CargoStatus;                           ///waiting-moving-delivered
	Truck* truckptr;
	int waitingDays;   ///for autoP
	int Priority;
public:
	Cargo(int cargoid, int readyDay, int readyHour, int loadtime, int deliveryDistance, int cargoCost, char cargoType, Truck* truckPtr= nullptr);
	void SetCargoID(int Id);
	int GetCargoID();
	
	void SetReadyDay(int R);
	int GetReadyDay();

	void SetReadyHour(int R);
	int GetReadyHour();

	void SetloadTime(int U);
	int GetloadTime();

	void SetDeliveryDistance(int D);
	int GetDeliveryDistance();

	void SetCargoCost(int CC);
	int GetCargoCost();

	void SetCargoType(char CT);
	char GetCargoType();

	void SetCargoStatus(char CS);
	char GetCargoStatus();

	void SetTruck(Truck* truckPTR);
	Truck* GetTruck();

	void SetWaitingDays(int waiting);
	int getWaitingDays();

	void incrementWaitingDays();

	void SetCargoPriority(Cargo* cargo);
	int GetCargoPriority();

	Cargo* getDataWithID(int cargoid);  //Used for the promotion event to retrieve normal cargo's data which to be promoted

	bool operator==(const Cargo&) const;
	const Cargo& operator=(const Cargo&);
	~Cargo();

};

