#include "lab2_drones_manager.hpp"


// TODO: Implement all of the listed functions below

DronesManager::DronesManager() : first(NULL),  last(NULL), size(0) {}

DronesManager::~DronesManager() {
	DroneRecord* cur = first;
	while (cur) {
		cur = cur->next;
		delete first;
		first = cur;
	}
	first = last = NULL;
	size = 0;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	//things to compare: droneID, range, yearBought, droneType, manufacturer, description, batteryType
	bool isEqual = true;
	isEqual = isEqual && lhs.droneID == rhs.droneID;
	isEqual = isEqual && lhs.range == rhs.range;
	isEqual = isEqual && lhs.yearBought == rhs.yearBought;
	isEqual = isEqual && lhs.droneType == rhs.droneType;
	isEqual = isEqual && lhs.manufacturer == rhs.manufacturer;
	isEqual = isEqual && lhs.description == rhs.description;
	isEqual = isEqual && lhs.batteryType == rhs.batteryType;
	return isEqual;
	return false;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if(size == 0)
		return true;
	else
		return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	DroneRecord* counter = first;
	if(size == 0)
		return DroneRecord(0);
	if(index>=size)
	{
		return DroneRecord(*last);
	}
	else
	{
		for(int count = 0; count < index; count++)
		{
			counter = counter->next;
		}
		return DroneRecord(*counter);
	}
}

unsigned int DronesManager::search(DroneRecord value) const {
	//DroneRecord* drone = &value;
	DroneRecord* drone = new DroneRecord(value);
	DroneRecord* dronePoint = first;
	if(size==0)
		return 0;
	else{
		for(int index = 0; index < size; index++)
		{	
			if(*dronePoint == *drone)
			{
				return index;
			}
			dronePoint = dronePoint -> next;
		}	
	}
	return 0;
}

void DronesManager::print() const {
	DroneRecord* counter = first;
	cout << "(";
	while(counter)
	{
		cout << "[" << counter-> droneID << " " << counter-> range << " " 
			 << counter->yearBought << endl; //counter->droneType << " " << counter -> manufacturer 
			 //<< " " << counter->description << " "
			 //<< counter->batteryType << " " <<"]" << endl;
		counter = counter->next;
		if(counter)
			cout << "->";
	}
	cout << ")\n";
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	//DroneRecord* drone = &value;
	DroneRecord* drone = new DroneRecord(value);
	DroneRecord* curr = first;
	for(int i = 1; i < index; i++)
	{
		curr = curr->next;
	}
	DroneRecord* temp = curr->next;
	DroneRecord* tempCurr = curr;
	curr->next = drone;
	drone->next = temp;
	temp->prev = drone;
	drone->prev = tempCurr;
	size++;
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* oldFirst = first;
	//DroneRecord* valueP = &value;
	DroneRecord* valueP = new DroneRecord(value);
	if(size == 0)
	{
		first = valueP;
		last = valueP;
	}
	else
	{
		valueP->next = oldFirst;
		first = valueP;
	}
	size++;
	return true;
	
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* drone = new DroneRecord(value);
	DroneRecord* curr = first; 
	if(size==0)
	{
		first = drone;
		last = drone;
	}
	else
	{
		last->next = drone;
		drone -> prev = last;
		last = drone;
	}
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	DroneRecord* curr = first;
	for(int i = 1; i < index; i++)
	{
		curr = curr->next;
	}
	DroneRecord* toDelete = curr->next;
	curr->next = curr->next -> next;
	curr->next->next->prev=curr->next;
	size--;
	delete toDelete;
	return true;
}

bool DronesManager::remove_front() {
	DroneRecord* toDelete = first;
	if(size == 0)
		return true;
	if(size == 1)
	{
		first = NULL;
		last = NULL;
	}
	else
	{
		first = first->next;
		first -> prev = NULL;
	}
	delete toDelete;	
	size--;
	return true;
}

bool DronesManager::remove_back() {
	DroneRecord* toDelete = last;
	if(size == 0)
		return true;
		
	if(size == 1) {
		first = NULL;
		last = NULL;
	}
	else
	{
		last = last->prev;
		last -> next = NULL;
	}
	size--;
	delete toDelete;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord* curr = first;
	//DroneRecord* drone = &value;
	DroneRecord* drone = new DroneRecord(value);
	if(size == 0)
		return true;
	else if(size == 1)
	{
		if(index==0)
		{
			DroneRecord* toDelete = first;
			first = drone;
			last = drone;		
			delete toDelete;
		}
	}
	else if(index==0)
	{
		DroneRecord* toDelete = first;
		DroneRecord* second = first->next;
		first = drone;
		first->next = second;
		delete toDelete;
	}
	else
	{
		for(int i =1; i < index; i++)
		{
			curr = curr->next;
		}
		DroneRecord* previousCurr = curr;
		DroneRecord* nextCurr = curr->next->next;
		*(curr->next) = value;
		curr->next->prev = previousCurr;
		curr->next->next = nextCurr;
	}
	
	return true;
}

bool DronesManager::reverse_list() {
	if(size == 0)
	{
		return true;
	}
	else
	{
		DroneRecord* before = NULL;
		DroneRecord* cur = first;
		DroneRecord* after = NULL;
		
		while(cur)
		{
			after = cur->next;
			cur->prev = after;
			cur->next = before;
			before = cur;
			cur = after;
		}
	
		last = first;
		first = before;
	}
	return true;
}

