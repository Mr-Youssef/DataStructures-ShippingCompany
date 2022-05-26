#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Queue.h"
#include "PriorityQ.h"
#include "Truck.h"
#include "Cargo.h"
#include "Event.h"
#include "UI.h"

class Event;
class UI;
class Company
{
private:
	// AvailableTrucks[0] -> NormalTrucks
	// AvailableTrucks[1] -> SpecialTrucks
	// AvailableTrucks[2] -> VIPTrucks
	// AvailableTrucks[3] -> NormalTrucksMaintenance 
	// AvailableTrucks[4] -> SpecialTrucksMaintenance
	// AvailableTrucks[5] -> VIPTrucksMaintenance
	
	//StatisticsArr[0] -> NormalCargo 
	//StatisticsArr[1] -> SpecialCargo
	//StatisticsArr[2] -> VIPCargo
	//StatisticsArr[3] -> NormalTruck 
	//StatisticsArr[4] -> SpecialTruck 
	//StatisticsArr[5] -> VIPTruck 
	//StatisticsArr[6] -> AutoPromotedCargo

	//TrucksInCheckUp[0] -> NormalTrucks
	//TrucksInCheckUp[1] -> SpecialTrucks
	//TrucksInCheckUp[2] -> VIPTrucks

	List<Cargo> normalCargos;
	Queue<Cargo> specialCargos;
	PriorityQ<Cargo> vipCargos;
	PriorityQ<Cargo> loadingCargos;
	PriorityQ<Cargo> movingCargos;
	Queue<Cargo> deliveredCargos;
	PriorityQ<Truck> AvailableTrucks[6];
	PriorityQ<Cargo> InExecution;
	Queue<Truck> VIPtrucks;
	Queue<Truck> SpecialTrucks;
	Queue<Truck> NormalTrucks;
	Queue<Truck> TrucksInCheckUp[3];
	Queue<Event> EventList;

	int availableTrucks = 0;
	int StatisticsArr[7];
	int noOfCargos;
	int noOfCancelled;
	int noOfEvents;
	float numberOfActive;  //numberofExecution
	float numberOfWaiting;
	int autoPromoted;
	int day;
	int hour;
	int maxWaitT = 0;

	UI* UIptr;	 // pointer to user interface
public:
	Company();
	/*Function that sets the available trucks according to the input file from the UI*/
	void setAvailableTrucks(int, int, int, int, int, int, int, int, int, int, int, int, int);

	/*Loads the file to get input, and check is simulation is possible*/ 
	bool Load();		

	/*Save an external output file*/
	void SaveFile();

	/*The main function that runs the code*/
	void Simulator();

	void Output();
	string stringNCargo(List<Cargo> x);
	string stringSCargo(Queue<Cargo>);
	string stringVCargo(PriorityQ<Cargo>);
	string stringEmptyTruck(PriorityQ<Truck>);
	string string_Delivered(Queue<Cargo> x);

	/*A function that checks all the waiting cargos and assign them if their preparation (ready) day is the current day*/
	void checkAndAssignCargo();
	bool assignTruck_Normal(PriorityQ<Truck>*, Cargo*&); //assign the normal cargo to a truck According to assignment order 
	bool assignTruck_VIP(PriorityQ<Truck>*, Cargo*&); //assign the vip cargo to a truck According to assignment order 
	bool assignTruck_Special(PriorityQ<Truck>*, Cargo*&); //assign the special cargo to a truck According to assignment order 
	void checkWaiting_VIP();
	void checkWaiting_Special();
	void checkWaiting_Normal();
	void moveToMoving_NCargo();
	void moveToMoving_SCargo();
	void moveToMoving_VCargo();

	/*A function that checks the cargos that have an assigned truck and move them to the loading cargos list*/
	void moveToLoading();

	/*A function that checks the cargos that have an assigned truck and move them to the moving cargos list*/
	void moveToMoving();

	/*A function that checks if the current day equals the delivered day of a certain cargo to be moved to delivered cargos list*/
	void moveToDelivered();

	/*Functions that move the trucks between lists*/
	void moveTruck(Cargo* cargo);
	void moveToAvailableTrucks();

	/*Getter for the current day*/
	int getDay();

	/*Getters for the average waiting and active days*/
	float getAvgWaitingDays();
	float getAvgActiveDays();

	/*getter for the auto promotion precentage*/
	void setAutoPromoted(int);
	float getAutoPromotedPercent();

	/*Function that autopromotes normal cargos after a certain period of time*/
	void autoPromote();

	/*Function that checks if the truck is in maintenance*/
	void checkInMaintenance();

	int getAvgUtilization();
	//void AssignCargo(Cargo* C);
	//void maxWait();
};