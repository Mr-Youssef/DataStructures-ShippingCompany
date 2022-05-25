#include "UI.h"

void UI::Error()
{
	cout << "Error due to improper input" << endl;
}

int UI::getNoOfNormalTrucks() const
{
	return noOfNormalTrucks;
}

int UI::getNoOfSpecialTrucks() const
{
	return noOfSpecialTrucks;
}

int UI::getNoOfVIPTrucks() const
{
	return noOfVIPTrucks;
}

int UI::getNoOfJForCheckup() const
{
	return noOfJForCheckup;
}

int UI::getNormalChkupDuration() const
{
	return normalChkupDuration;
}

int UI::getSpecialChkupDuration() const
{
	return specialChkupDuration;
}

int UI::getVIPChkupDuration() const
{
	return vipChkupDuration;
}

int UI::getAutoP() const
{
	return AutoP;
}

int UI::getNoOfEvent() const
{
	return noOfEvent;
}

void UI::setAutoP(int autoprom)
{
	if (autoprom >= 0)
		AutoP = autoprom;
	else AutoP = 0;
}

bool UI::Read_File(Queue<Event>& EventList, PriorityQ<Truck>& NormalTruck, PriorityQ<Truck>& SpecialTruck, PriorityQ<Truck>& VIPTruck, int& NoOFcargos, int& NoofCancelled)
{
	bool Valid;
	string filename;
	cout << "Enter file name to be loaded: ";
	cin >> filename;
	cout << endl;
	filename += ".txt"; // adds .txt extension to filename

	ifstream fin;
	fin.open(filename);

	if (!fin.is_open()) // makes sure file was opened successfully
	{
		cout << "\t" << filename + " not found" << endl;
		exit(1);
	}

	Fill_Trucks(fin, NormalTruck, SpecialTruck, VIPTruck); // fills the rover lists

	fin >> AutoP;
	fin >> MaxW;

	Valid = Fill_Events(fin, EventList, NoOFcargos, NoofCancelled);

	fin.close();

	return Valid;
}

bool UI::Fill_Events(ifstream& fin, Queue<Event>& Event_List, int& NoOFcargos, int& NoofCancelled)
{
	char EType = 'un';	//Event Type
	char CType = 'un';	//Cargo Type
	int ED = -1, EH = -1, id = -1, dist = -1, LT = -1, cost = -1, extraMoney = -1;

	fin >> noOfEvent;
	// There are no trucks, but there are cargos
	// so simulation can't run
	if (noOfNormalTrucks == 0 && noOfSpecialTrucks == 0 && noOfVIPTrucks == 0 && noOfEvent != 0)
	{
		return false;
	}

	// There are trucks, but their speeds = 0
	// so simulation can't run 
	if (noOfEvent != 0 && ((noOfNormalTrucks != 0 && speedNormalTrucks == 0) || (noOfSpecialTrucks != 0 && speedSpecialTrucks == 0) || (noOfVIPTrucks != 0 && speedVIPTrucks == 0)))
	{
		return false;
	}

	for (int i = 0; i < noOfEvent; i++)  // loads the data of each event
	{
		fin >> EType;

		// there are x cargos, but no x trucks
		// so simulation can't run properly

		if (EType == 'R')
		{
			fin >> CType >> ED;
			fin.ignore(1, '\n');
			fin >> EH >> id >> dist >> LT >> cost;

			if (noOfNormalTrucks == 0 && CType == 'N' || noOfSpecialTrucks == 0 && CType == 'S' || noOfVIPTrucks == 0 && CType == 'V')
			{
				return false;
			}

			Preparation* prepare = new Preparation(id, ED, EH, CType, 0, LT, dist, cost);
			NoOFcargos++;
			Event_List.enqueue(prepare);
		}
		else if (EType == 'X')
		{
			fin >> ED;
			fin.ignore(1, '\n');
			fin >> EH >> id;
			Cancellation* cancel = new Cancellation(id, ED, EH);
			NoofCancelled++;
			Event_List.enqueue(cancel);
		}
		else if (EType == 'P')
		{
			fin >> ED;
			fin.ignore(1, '\n');
			fin >> EH >> id >> extraMoney;
			Promotion* promote = new Promotion(id, ED, EH, 'N', 0, LT, dist, cost, extraMoney);
			Event_List.enqueue(promote);
		}
	}

	return true; // simulation possible
}

void UI::Fill_Trucks(ifstream& fin, PriorityQ<Truck>& normalTruck, PriorityQ<Truck>& specialTruck, PriorityQ<Truck>& vipTruck)  // Takes empty list of trucks from Company
{
	Truck* truck = nullptr;

	// takes input from file
	fin >> noOfNormalTrucks >> noOfSpecialTrucks >> noOfVIPTrucks;
	fin >> speedNormalTrucks >> speedSpecialTrucks >> speedVIPTrucks;
	fin >> capacityNormal >> capacitySpecial >> capacityVIP;
	fin >> noOfJForCheckup >> normalChkupDuration >> specialChkupDuration >> vipChkupDuration;
	for (int i = 0; i < noOfNormalTrucks; i++)
	{
		truck = new Truck('N', speedNormalTrucks, capacityNormal, noOfJForCheckup, normalChkupDuration);									// creates the truck
		normalTruck.enqueue(truck, ((Truck*)truck)->getSpeed());	// places it in the list, sorted
																							// descendingly according to speed
	}
	for (int i = 0; i < noOfSpecialTrucks; i++)
	{
		truck = new Truck('S', speedSpecialTrucks, capacitySpecial, noOfJForCheckup, specialChkupDuration);						// creates the rover
		specialTruck.enqueue(truck, ((Truck*)truck)->getSpeed()); // places it in the list, sorted
																				// descendingly according to speed
	}
	for (int i = 0; i < noOfVIPTrucks; i++)
	{
		truck = new Truck('V', speedVIPTrucks, capacityVIP, noOfJForCheckup, vipChkupDuration);				// creates the rover
		vipTruck.enqueue(truck, ((Truck*)truck)->getSpeed()); // places it in the list, sorted
																		// descendingly according to speed
	}
}

int UI::getMode()
{
	cout << "Welcome To Our Shipping Company !\n";
	cout << "Please choose mode of operation: 1-Interactive   2-Step-by-step   3-Silent\n";
	cin >> mode;
	return mode;
}

void UI::Print(string line1, string line2, string line3, string line4, string line5, string line6, string line7)
{
	string x = "\n-------------------------------------------------------\n";
	if (mode == 1) {
		cin.ignore();
		cout << line1 << endl << line2 << endl << line3 << endl << line4 << endl << line5 << endl << line6 << endl << line7 << endl << endl;

	}
	/*else if (mode == 2) {
		cout << line1 << endl << line2 << x << line3 << x << line4 << x << line5 << x << line6 << endl << endl;
		Sleep(1000);
	}*/
}
//=============PHASE 2
//void UI::SaveFile(string line1, string line2, string line3, string line4, float wait, float exec, int AutoP)
//{
//	if (mode == 3)
//	{
//		cout << "Silent Mode \nSimulation Starts...\n";
//		cout << "Simulation ends, Output file created\n\n";
//	}
//
//	ofstream saved_file;
//	saved_file.open("saved_file.txt", ios::out | ios::trunc);
//	saved_file << line1 << endl << line2 << endl << line3 << endl << line4 << endl;
//	saved_file << "Avg. Wait = " << setprecision(4) << wait << ", Avg. Exec = " << setprecision(4) << exec;
//	saved_file << endl << "Auto-promoted = " << AutoP;
//	saved_file.close();
//}

