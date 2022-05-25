#include "Cargo.h"
#include <iostream>
using namespace std;

Cargo::Cargo(int cargoid, int readyTime, int loadtime, int deliveryDistance, int cargoCost, char cargoType, Truck* truckPtr)
{
	SetCargoID(cargoid);
	SetReadyTime(readyTime);
	SetloadTime(loadtime);
	SetDeliveryDistance(deliveryDistance);
	SetCargoCost(cargoCost);
	SetCargoType(cargoType);
	SetTruck(truckPtr);
	waitingDays = 0;
}

void Cargo::SetCargoID(int Id) { cargoID = Id; }

void Cargo::SetReadyTime(int R) { ReadyTime = R; }

void Cargo::SetloadTime(int U) { loadTime = U; }

void Cargo::SetDeliveryDistance(int D) { DeliveryDistance = D; }

void Cargo::SetCargoCost(int CC) { CargoCost = CC; }

void Cargo::SetCargoType(char CT) { CargoType = CT; }

void Cargo::SetCargoStatus(char CS) { CargoStatus = CS; }

void Cargo::SetTruck(Truck* truckPTR) { this->truckptr = truckPTR; }

void Cargo::SetWaitingDays(int waiting) { waitingDays = waiting; }

int Cargo::GetCargoID() { return cargoID; }

char Cargo::GetCargoType() { return CargoType; }

int Cargo::GetReadyTime() { return ReadyTime; }

int Cargo::GetloadTime() { return loadTime; }

int Cargo::GetDeliveryDistance() { return DeliveryDistance; }

int Cargo::GetCargoCost() { return CargoCost; }

char Cargo::GetCargoStatus() { return CargoStatus;  }

Truck* Cargo::GetTruck() { return truckptr; }

int Cargo::getWaitingDays() { return waitingDays; }

void Cargo::incrementWaitingDays() { waitingDays++; }

void Cargo::SetCargoPriority(Cargo* cargo) {
	Priority = cargo->GetCargoCost() / (cargo->GetDeliveryDistance() * (cargo->GetReadyTime()));
}
int Cargo::GetCargoPriority() {
	return Priority;
}

bool Cargo::operator==(const Cargo &over) const
{
	if (cargoID == over.cargoID)
	{
		return true;
	}
	else
	{
		return false;
	}
		
}
const Cargo& Cargo::operator=(const Cargo& copy)
{
	cargoID = copy.cargoID;
	ReadyTime = copy.ReadyTime;
	loadTime = copy.loadTime;
	DeliveryDistance = copy.DeliveryDistance;
	CargoCost = copy.CargoCost;
	CargoType = copy.CargoType;
	CargoStatus = copy.CargoStatus;
	truckptr = copy.truckptr;
	return *this;
}

//Cargo* getDataWithID(int cargoid)
//{
//	return;
//}
Cargo::~Cargo() {}
