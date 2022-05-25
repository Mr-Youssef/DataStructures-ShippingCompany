#pragma once
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Queue.h"
#include "PriorityQ.h"
#include "Cargo.h"
#include "Event.h"
#include "Preparation.h"
#include "Cancellation.h"
#include "Promotion.h"
#include "Company.h"

using namespace std;

class UI
{
private:
	int noOfNormalTrucks;			// number of normal trucks
	int noOfSpecialTrucks;			// number of special trucks
	int noOfVIPTrucks;		    	// number of vip trucks
	int speedNormalTrucks;			// speed of normal trucks
	int speedSpecialTrucks;			// speed of special trucks
	int speedVIPTrucks;			    // speed of vip trucks
	int capacityNormal;
	int capacitySpecial;
	int capacityVIP;
	int noOfJForCheckup;             // number of journeys before checkup
	int normalChkupDuration;		        // checkup duration in hours for normal trucks
	int specialChkupDuration;		// checkup duration in hours for special trucks
	int vipChkupDuration;		// checkup duration in hours for vip trucks
	int AutoP;				// number of days after which a normal cargo is automatically promoted to a vip cargo
	int MaxW;			
	int noOfEvent;        // number of events
	int mode;				// desired output mode

	bool Fill_Events(ifstream& fin, Queue<Event>& Event_List, int& NoOFcargos, int& NoofCancelled); // Takes empty list of events from MarsStation
																 // and fills it with the events read from file
	void Fill_Trucks(ifstream& fin, PriorityQ<Truck>& normalTruck, PriorityQ<Truck>& specialTruck, PriorityQ<Truck>& vipTruck);				// Takes empty list of trucks from Company

public:
	bool Read_File(Queue<Event>& EventList, PriorityQ<Truck>& NormalTruck, PriorityQ<Truck>& SpecialTruck, PriorityQ<Truck>& VIPTruck, int& NoOFcargos, int& NoofCancelled);	// reads input from file, and calls Fill_Events and Fill_Trucks

	int getNoOfNormalTrucks() const;
	int getNoOfSpecialTrucks() const;
	int getNoOfVIPTrucks() const;

	int getNoOfJForCheckup() const;
	int getNormalChkupDuration() const;
	int getSpecialChkupDuration() const;
	int getVIPChkupDuration() const;
	int getAutoP() const;
	int getNoOfEvent() const;
	void setAutoP(int);
	void Print(string, string, string, string, string, string, string);
	//void SaveFile(string, string, string, string, float, float, int);
	int getMode();
	void Error();
};