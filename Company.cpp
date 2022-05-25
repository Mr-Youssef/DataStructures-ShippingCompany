#include "Company.h"

/*Constructor*/
Company::Company()
{
	UIptr = new UI();
	day = 0;
	hour = 0;
	noOfCargos = 0;
	noOfCancelled = 0;
	noOfEvents = 0;
	numberOfWaiting = 0;
	numberOfActive = 0;
	autoPromoted = 0;
	for (int i = 0; i < 7; i++)
	{
		StatisticsArr[i] = 0;
	}
}

/////////////////
	//   PHASE 2   //
	/////////////////
//==============For Bonus 3 ArrOfSpeed will be parameters instead of NS, SS, VS=============// 
//void Company::setAvailableTrucks(int N, int S, int V, int NS, int SS, int VS, int NTC, int STC, int VTC, int J, int CN, int CS, int CV)
//{
//	/*Saving the number of each truck for each type*/
//	StatisticsArr[3] = N;
//	StatisticsArr[4] = S;
//	StatisticsArr[5] = V;
//	int id = 1;
//
//	/*Looping on each truck type and assign them to the available truck list*/
//	for (int i = 0; i < N; i++)
//	{
//
//		Truck* normal = new Truck('N', NS, NTC, J, CN);
//		normal->setTruckID(id);
//		id++;
//		AvailableTrucks[0].enqueue(normal, NS);
//	}
//
//	for (int i = 0; i < S; i++)
//	{
//		Truck* special = new Truck('S', SS, STC, J, CS);
//		special->setTruckID(id);
//		id++;
//		AvailableTrucks[1].enqueue(special, SS);
//	}
//
//	for (int i = 0; i < V; i++)
//	{
//		Truck* vip = new Truck('V', VS, VTC, J, CV);
//		vip->setTruckID(id);
//		id++;
//		AvailableTrucks[0].enqueue(vip, VS);
//	}
//}

bool Company::Load()
{
	bool Valid = UIptr->Read_File(EventList, AvailableTrucks[0], AvailableTrucks[1], AvailableTrucks[2], noOfCargos, noOfCancelled);

	if (Valid)
	{
		UIptr->getMode();
		noOfEvents = EventList.getSize();
	}
	return Valid;
}

void Company::Simulator()
{
	bool isPossible = Load();
	if (!isPossible)
	{
		UIptr->Error();
		return;
	}
	//simulation stops when event list is empty and all cargos delivered
	while (!EventList.isEmpty() && ((deliveredCargos.getSize() - noOfCancelled) != (noOfCargos - noOfCancelled)))
	{
		day++;
		hour = 0;
		for (int i = 0; i < 24; i++)
		{
			Node<Event>* tempNode;
			EventList.peek(tempNode);
			Event* temp;
			temp = tempNode->getData();
			while (temp->GetEventDay() == day && temp->GetEventHour() == hour)
			{
				temp->Execute(normalCargos, specialCargos, vipCargos, StatisticsArr);
				EventList.dequeue(tempNode);

				bool check = EventList.peek(tempNode);
				if (!check)
					break;
				temp = tempNode->getData();
			}
			if (hour % 5 == 0)
			{
				moveToDelivered();
			}
			if ((deliveredCargos.getSize() - noOfCancelled) == (noOfCargos - noOfCancelled))
			{
				break;
			}
			hour++;
		}
		
		

	}
	Output();
}

void Company::Output()
{
	string line1, line2, line3, line4, line5, line6, line7;

	line1 = "Current Time (Day:Hour):" + to_string(day) + ":" + to_string(hour);

	int waitingCargos = normalCargos.getLength() + specialCargos.getSize() + vipCargos.getSize();
	line2 = to_string(waitingCargos) + " Waiting Cargos: " + stringNCargo(normalCargos) + " " + stringSCargo(specialCargos) + " " + stringVCargo(vipCargos); // with truck ID

	
	line3 = "0 Loading Trucks: ";  //phase 2

	int availableTrucks = AvailableTrucks[0].getSize() + AvailableTrucks[1].getSize() + AvailableTrucks[2].getSize();
	line4 = to_string(availableTrucks) + " Empty Trucks: " + "[1], [2], [3], (4), (5), (6), {7}, {8}";  //phase 2

	
	line5 = "0 Moving Cargos: ";  //phase 2


	line6 = "0 In-Checkup Trucks: ";  //phase 2

	int noOfDelivered = deliveredCargos.getSize();
	line7 = to_string(noOfDelivered) + " Delivered Cargos: " + string_Delivered(deliveredCargos);

	UIptr->Print(line1, line2, line3, line4, line5, line6, line7);
}

string Company::stringNCargo(List<Cargo> x)
{
	List<Cargo> tempNCargo = x;
	int no = 0;
	int k = 0;
	int* arrk = new int[noOfEvents];
	while (!tempNCargo.isEmpty())
	{
		no++;
		arrk[k++] = tempNCargo.getEntry(1)->GetCargoID();
		tempNCargo.remove(1);
	} //transferring from list to array

	if (k != 0)
	{
		string M = "[" + to_string(arrk[0]);
		for (int i = 1; i < k; i++)
		{
			M = M + ", " + to_string(arrk[i]);
		}
		return M + "]";
	}
	else
		return "";
}

string Company::stringSCargo(Queue<Cargo> x)
{
	Queue<Cargo> Temp = x;

	int size = Temp.getSize();
	if (size == 0) return "";

	string P = "(";

	for (int i = 0; i < size; i++)
	{
		Cargo* cur;
		Node<Cargo>* temppp;
		Temp.dequeue(temppp);
		cur = temppp->getData();
		P += to_string(cur->GetCargoID()) + ", ";
	}
	if (P == "(") P = "";
	if (P != "") P.pop_back(), P.pop_back(), P += ")";
	return P + " ";
}

string Company::stringVCargo(PriorityQ<Cargo> x)
{
	PriorityQ<Cargo> Temp = x;

	int size = Temp.getSize();
	if (size == 0) return "";

	string E = "{";

	for (int i = 0; i < size; i++)
	{
		Cargo* curr;
		Node<Cargo>* tempppp;
		Temp.dequeue(tempppp);
		curr = tempppp->getData();
		E += to_string(curr->GetCargoID()) + ", ";
	}
	if (E == "{") E = "";
	if (E != "") E.pop_back(), E.pop_back(), E += "}";
	return E + " ";
}

string Company::stringEmptyTruck(PriorityQ<Truck> x) //to be edited in phase 2
{
	PriorityQ<Truck> Temp = x;

	int size = Temp.getSize();
	if (size == 0)
		return "";
	string M;
	Truck* cur;
	Node<Truck>* temppp;
	Temp.dequeue(temppp);
	cur = temppp->getData();
	if (cur->getTruckType() == 'N')
	{
		M = "[" + to_string(cur->getTruckID()) + "], ";
	}
	else if (cur->getTruckType() == 'S')
	{
		M = "(" + to_string(cur->getTruckID()) + "), ";
	}
	else if (cur->getTruckType() == 'V')
	{
		M = "{" + to_string(cur->getTruckID()) + "}, ";
	}
	for (int i = 1; i < size; i++)
	{
		Temp.dequeue(temppp);
		cur = temppp->getData();
		if (cur->getTruckType() == 'N')
		{
			M += "[" + to_string(cur->getTruckID()) + "], ";
		}
		else if (cur->getTruckType() == 'S')
		{
			M += "(" + to_string(cur->getTruckID()) + "), ";
		}
		else if (cur->getTruckType() == 'V')
		{
			M += "{" + to_string(cur->getTruckID()) + "}, ";
		}
	}
	return M;


	//================
	/*PriorityQ<Truck> Temp = x;

	int size = Temp.getSize();
	if (size == 0) return "";

	string waitingN = "[";
	string waitingS = "(";
	string waitingV = "{";

	for (int i = 0; i < size; i++)
	{
		Truck* cur;
		Node<Truck>* tempppp;
		Temp.dequeue(tempppp);
		cur = tempppp->getData();

		if (dynamic_cast<Rover_Emergency*>(cur))
			waitingN += to_string(cur->getTruckID()) + ", ";

		else if (dynamic_cast<Rover_Polar*>(cur))
			waitingS += to_string(cur->getTruckID()) + ", ";

		else if (dynamic_cast<Rover_Mountainous*>(cur))
			waitingV += to_string(cur->getTruckID()) + ", ";
	}
	if (waitingN == "[") waitingN = "";
	if (waitingS == "(") waitingS = "";
	if (waitingV == "{") waitingV = "";
	if (waitingN != "") waitingN.pop_back(), waitingN.pop_back(), waitingN += "]";
	if (waitingS != "") waitingS.pop_back(), waitingS.pop_back(), waitingS += ")";
	if (waitingV != "") waitingV.pop_back(), waitingV.pop_back(), waitingV += "}";
	return waitingN + " " + waitingS + " " + waitingV;*/
}

string Company::string_Delivered(Queue<Cargo> x)
{
	Queue<Cargo> Temp = x;

	int size = Temp.getSize();
	if (size == 0) 
		return "";
	string M;
	Cargo* cur;
	Node<Cargo>* temppp;
	Temp.dequeue(temppp);
	cur = temppp->getData();
	if (cur->GetCargoType() == 'N')
	{
		M = "[" + to_string(cur->GetCargoID()) + "] ";
	}
	else if (cur->GetCargoType() == 'S')
	{
		M = "(" + to_string(cur->GetCargoID()) + ") ";
	}
	else if (cur->GetCargoType() == 'V')
	{
		M = "{" + to_string(cur->GetCargoID()) + "} ";
	}
	for (int i = 1; i < size; i++)
	{
		Temp.dequeue(temppp);
		cur = temppp->getData();
		if (cur->GetCargoType() == 'N')
		{
			M += "[" + to_string(cur->GetCargoID()) + "] ";
		}
		else if (cur->GetCargoType() == 'S')
		{
			M += "(" + to_string(cur->GetCargoID()) + ") ";
		}
		else if (cur->GetCargoType() == 'V')
		{
			M += "{" + to_string(cur->GetCargoID()) + "} ";
		}
	}
	return M;
}

void Company::checkAndAssignCargo()
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}

bool Company::assignTruck_Normal(PriorityQ<Truck>* truckArray, Cargo*& tempCargo)
{
	Node<Truck>* tempNode; //to get the 1st available normal truck in it
	bool test = false;
	if (truckArray[0].dequeue(tempNode))
	{
		/*Checking no. of waiting normal cargos >= capacity of the 1st available normal truck for the loading rule*/
		if (normalCargos.getLength() >= tempNode->getData()->getTruckCapacity())
			test = true;
		else
			test = false;
	}
	if (test)
	{
		/*If the available normal truck priority queue was not empty, dequeue the truck in a temporary node, and add this truck to the cargo*/
		for (int i = 0; i < tempNode->getData()->getTruckCapacity(); i++)
		{ 
			/*Remove the waiting normal cargo and assign it to the normal truck*/
			tempCargo = normalCargos.getEntry(1);
			normalCargos.remove(1);
			tempCargo->SetTruck(tempNode->getData());
			tempNode->getData()->incrementCargoCount();
		}
		return test;
	}
	/*If the available normal truck priqueue was empty, check available vip trucks*/
	if (truckArray[2].dequeue(tempNode))
	{
		/*Checking no. of waiting normal cargos >= capacity of the 1st available normal truck for the loading rule*/
		if (normalCargos.getLength() >= tempNode->getData()->getTruckCapacity())
			test = true;
		else
			test = false;
	}
	if (test)
	{
		for (int i = 0; i < tempNode->getData()->getTruckCapacity(); i++)
		{
			/*Remove the waiting normal cargo and assign it to the vip truck*/
			tempCargo = normalCargos.getEntry(1);
			normalCargos.remove(1);
			tempCargo->SetTruck(tempNode->getData());
			tempNode->getData()->incrementCargoCount();
		}
		return test;
	}
	//if (!test)
	//{
	//	/*If no trucks were found in the available vip trucks priqueue, check normal in maintenance trucks */
	//	test = truckArray[3].dequeue(tempNode);
	//	if (test)
	//	{
	//		tempCargo->SetTruck(tempNode->getData());
	//		tempNode->getData()->incrementCargoCount();
	//	}
	//}
	return test;
}
bool Company::assignTruck_VIP(PriorityQ<Truck>* truckArray, Cargo*& tempCargo)
{
	Node<Truck>* tempNode;
	/*Checking if the available vip truck priqueue is not empty*/
	bool test = false;
	if (truckArray[2].dequeue(tempNode))
	{
		/*Checking no. of waiting normal cargos >= capacity of the 1st available normal truck for the loading rule*/
		if (vipCargos.getSize() >= tempNode->getData()->getTruckCapacity())
			test = true;
		else
			test = false;
	}
	if (test)
	{
		Node<Cargo>* tempNodeC;
		for (int i = 0; i < tempNode->getData()->getTruckCapacity(); i++)
		{
			/*Remove the waiting vip cargo and assign it to the vip truck*/

			vipCargos.dequeue(tempNodeC);
			tempCargo = tempNodeC->getData();
			tempCargo->SetTruck(tempNode->getData());
			tempNode->getData()->incrementCargoCount();
		}
		return test;
	}
	/*If no vip trucks were available for this vip cargo, check available normal trucks*/
	if (truckArray[0].dequeue(tempNode))
	{
		/*Checking no. of waiting vip cargos >= capacity of the 1st available normal truck for the loading rule*/
		if (vipCargos.getSize() >= tempNode->getData()->getTruckCapacity())
			test = true;
		else
			test = false;
	}
	if (test)
	{
		Node<Cargo>* tempNodeC;
		for (int i = 0; i < tempNode->getData()->getTruckCapacity(); i++)
		{
			/*Remove the waiting vip cargo and assign it to the normal truck*/

			vipCargos.dequeue(tempNodeC);
			tempCargo = tempNodeC->getData();
			tempCargo->SetTruck(tempNode->getData());
			tempNode->getData()->incrementCargoCount();
		}
		return test;
	}
	/*If no normal trucks were available, check available special trucks*/
	if (truckArray[1].dequeue(tempNode))
	{
		/*Checking no. of waiting vip cargos >= capacity of the 1st available special truck for the loading rule*/
		if (vipCargos.getSize() >= tempNode->getData()->getTruckCapacity())
			test = true;
		else
			test = false;
	}
	if (test)
	{
		Node<Cargo>* tempNodeC;
		for (int i = 0; i < tempNode->getData()->getTruckCapacity(); i++)
		{
			/*Remove the waiting vip cargo and assign it to the special truck*/
			vipCargos.dequeue(tempNodeC);
			tempCargo = tempNodeC->getData();
			tempCargo->SetTruck(tempNode->getData());
			tempNode->getData()->incrementCargoCount();
		}
		return test;
	}
	/*If all available trucks were not present, check vip trucks in maintenance*/
	//if (!test)
	//{
	//	test = truckArray[5].dequeue(tempNode);
	//	/*If a truck was found in the "vip trucks in maintenance" priqueue, assign it to the cargo*/
	//	if (test)
	//	{
	//		tempCargo->SetTruck(tempNode->getData());
	//		tempNode->getData()->incrementCargoCount();
	//	}
	//}
	return test;
}
bool Company::assignTruck_Special(PriorityQ<Truck>* truckArray, Cargo*& tempCargo)
{
	Node<Truck>* tempNode;
	/*Checking the available special trucks priqueue is not empty*/
	bool test = false;
	if (truckArray[1].dequeue(tempNode))
	{
		/*Checking no. of waiting special cargos >= capacity of the 1st available special truck for the loading rule*/
		if (specialCargos.getSize() >= tempNode->getData()->getTruckCapacity())
			test = true;
		else
			test = false;
	}
	if (test)
	{
		/*If the available special trucks priqueue was not empty, dequeue the truck in a temporary node, and add this truck to the cargo*/
		Node<Cargo>* tempNodeC;
		for (int i = 0; i < tempNode->getData()->getTruckCapacity(); i++)
		{
			/*Remove the waiting special cargo and assign it to the special truck*/
			specialCargos.dequeue(tempNodeC);
			tempCargo = tempNodeC->getData();
			tempCargo->SetTruck(tempNode->getData());
			tempNode->getData()->incrementCargoCount();
		}
		return test;
	}
	//if (!test)
	//{
	//	/*If the available polar rovers priqueue is empty, check the polar rovers in maintenance */
	//	test = roverArray[4].dequeue(tempNode);
	//	/*If the special trucks in maintenance was not empty, assign the in-maintenance truck to the cargo*/
	//	if (test)
	//	{
	//		tempCargo->SetTruck(tempNode->getData());
	//		tempNode->getData()->incrementCargoCount();
	//	}
	//}
	return test;

}
void Company::checkWaiting_VIP()
{
	Node<Cargo>* tempNode;
	Cargo* tempCargo;
	int cDay;
	PriorityQ<Cargo> tempPriQ;
	/*Checking if the waiting vip Cargos list is not empty*/
	if (!vipCargos.isEmpty())
	{
		vipCargos.dequeue(tempNode);
		tempCargo = tempNode->getData();
		cDay = tempCargo->GetReadyTime();
		/*Checking if the day of the preparation is smaller than or equal the current day*/
		/*Condition was not met, enqueue the dequeued Node to a temporary Priqueue*/
		if (cDay > day)
		{
			tempPriQ.enqueue(tempCargo, tempNode->getPriority());

		}
		else
		{
			/* While the Condition is met, Assign a truck to the dequeued cargo*/

			while (cDay <= day)
			{
				bool test = assignTruck_VIP(AvailableTrucks, tempCargo);
				/*Checking if there is available truck to be assigned to the waiting cargos*/
				if (test && tempNode)
				{
					tempPriQ.enqueue(tempCargo, tempNode->getPriority());
					bool can = vipCargos.dequeue(tempNode);
					tempCargo = tempNode->getData();
					cDay = tempCargo->GetReadyTime();
					if (!can)
					{
						tempNode = NULL;
						break;
					}

				}
				/*If there is no suitable truck to assign then increment the waiting days*/
				else
				{
					tempCargo->incrementWaitingDays();
					tempPriQ.enqueue(tempCargo, tempNode->getPriority());
					break;

				}

			}
		}
		/*Incrementing the rest of the cargos in the waiting*/
		while (vipCargos.dequeue(tempNode))
		{
			tempCargo = tempNode->getData();
			cDay = tempCargo->GetReadyTime();
			if (cDay <= day)
				tempCargo->incrementWaitingDays();
			tempPriQ.enqueue(tempCargo, tempNode->getPriority());
		}
		/*Adding the rest of the list back in its original list*/
		while (tempPriQ.dequeue(tempNode))
		{
			tempCargo = tempNode->getData();
			vipCargos.enqueue(tempCargo, tempNode->getPriority());
		}
	}
}

void Company::checkWaiting_Special()
{
	Node<Cargo>* tempNode;
	Cargo* tempCargo;
	int cDay;
	Queue<Cargo> tempQ;
	/*Checking if the waiting special cargos list is not empty*/
	if (!specialCargos.isEmpty())
	{
		specialCargos.dequeue(tempNode);
		tempCargo = tempNode->getData();
		cDay = tempCargo->GetReadyTime();
		/*Checking if the day of the preparation is smaller than or equal the current day*/
		/*Condition was not met, enqueue the dequeued Node to a temporary queue*/
		if (cDay > day)
		{
			tempQ.enqueue(tempCargo);
		}
		else
		{
			/* While Condition is met, Assign a truck to the dequeued cargo*/
			while (cDay <= day)
			{
				bool test = assignTruck_Special(AvailableTrucks, tempCargo);
				/*Checking if there is available truck to be assigned to the waiting cargos*/
				if (test && tempNode)
				{
					tempQ.enqueue(tempCargo);
					bool can = specialCargos.dequeue(tempNode);
					tempCargo = tempNode->getData();
					cDay = tempCargo->GetReadyTime();
					if (!can)
					{
						tempNode = NULL;
						break;
					}

				}
				/*If there is no suitable truck to assign then increment the waiting days*/
				else
				{
					tempCargo->incrementWaitingDays();
					tempQ.enqueue(tempCargo);
					break;

				}

			}
		}
	}
	/*Incrementing the rest of the cargos in the waiting*/
	while (specialCargos.dequeue(tempNode))
	{
		tempCargo = tempNode->getData();
		cDay = tempCargo->GetReadyTime();
		if (cDay <= day)
			tempCargo->incrementWaitingDays();
		tempQ.enqueue(tempCargo);
	}
	while (tempQ.dequeue(tempNode))
	{
		tempCargo = tempNode->getData();
		specialCargos.enqueue(tempCargo);
	}
}

void Company::checkWaiting_Normal()
{
	Cargo* tempCargo;
	int cDay;
	List<Cargo> tempL;
	while (!normalCargos.isEmpty())
	{
		tempCargo = normalCargos.getEntry(1);
		normalCargos.remove(1);
			cDay = tempCargo->GetReadyTime();
			/*Checking if the day of the preparation is smaller than or equal the current day*/
			if (cDay > day)
			{
				tempL.InsertEnd(tempCargo);
				break;
			}
			else
			{
				while (cDay <= day)
				{
					bool test = assignTruck_Normal(AvailableTrucks, tempCargo);
					/*Checking if there is available truck to be assigned to the waiting cargos*/
					if (test)
					{
						tempL.InsertEnd(tempCargo);
						tempCargo = normalCargos.getEntry(1);
						normalCargos.remove(1);
						cDay = tempCargo->GetReadyTime();


					}
					else
						/*If there is no suitable truck to assign then increment the waiting days*/
					{
						tempCargo->incrementWaitingDays();
						tempL.InsertEnd(tempCargo);
						break;

					}

				}
			}
	}
	while (normalCargos.getEntry(1) != nullptr)
	{
		normalCargos.remove(1);
		cDay = tempCargo->GetReadyTime();
		if (cDay <= day)
			tempCargo->incrementWaitingDays();
		tempL.InsertEnd(tempCargo);
	}
}

void Company::moveToLoading()
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}

void Company::moveToMoving()
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}

void Company::moveToDelivered()
{
	//In phase 1 we will move the waiting cargo to delivered cargo list directly==================
	//In phase 2 this will change, (waiting->loading->moving->delivered)==========================
	//Cargo tempnormalCargo();
	Node<Cargo>* tempspecialNode;
	Cargo* tempSpecialCargo;
	Node<Cargo>* tempVIPNode;
	Cargo* tempVIPCargo;
	//move waiting normal cargo to delivered
	while (!normalCargos.isEmpty())
	{
		Cargo* tempnormalCargo = normalCargos.getEntry(1);
		Cargo* tempo = tempnormalCargo;
		deliveredCargos.enqueue(tempo);
		normalCargos.remove(1);
	}
	//move waiting special cargo to delivered
	while (!specialCargos.isEmpty())
	{
		specialCargos.dequeue(tempspecialNode);
		tempSpecialCargo = tempspecialNode->getData();
		deliveredCargos.enqueue(tempSpecialCargo);
	}
	//move waiting vip cargo to delivered
	while (!vipCargos.isEmpty())
	{
		vipCargos.dequeue(tempVIPNode);
		tempVIPCargo = tempVIPNode->getData();
		deliveredCargos.enqueue(tempVIPCargo);
	}
}

void Company::moveTruck(Cargo* cargo)
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}

void Company::moveToAvailableTrucks()
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}

int Company::getDay()
{
	return day;
}

float Company::getAvgWaitingDays() //Should be used after all loops (calculations occur after end of while loop)
{
	return numberOfWaiting;
}
float Company::getAvgActiveDays() //Should be used after all loops (calculations occur after end of while loop)
{
	return numberOfActive;
}

void Company::setAutoPromoted(int autoP)
{
	autoPromoted = autoP;
}
float Company::getAutoPromotedPercent()
{
	if (StatisticsArr[0] == 0)
	{
		return 0;
	}
	return (((float)StatisticsArr[6] / ((float)StatisticsArr[6] + (float)StatisticsArr[0]))) * 100;
}

void Company::autoPromote()
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}

void Company::checkInMaintenance()
{
	/////////////////
	//   PHASE 2   //
	/////////////////
}