#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

using namespace std;
class DronesManagerTest {
public:
	
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		//what we need for constructor unsigned int newDroneID, unsigned int newRange, unsigned int newYearBought, string newDroneType, string newManufacturer, string newDescription, string newBatteryType) :
	    DronesManager manager1;
	    
	    DronesManager::DroneRecord drone1 = DronesManager::DroneRecord(100);
		DronesManager::DroneRecord drone2 = DronesManager::DroneRecord(101);
		DronesManager::DroneRecord drone3 = DronesManager::DroneRecord(102);
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(101));
		manager1.insert_back(DronesManager::DroneRecord(102));
		//Testing for search()
		ASSERT_TRUE(manager1.search(drone1) == 0)
		ASSERT_TRUE(manager1.search(drone2) == 1)
		ASSERT_TRUE(manager1.search(drone3) == 2)
		//Testing for select()
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(100))
		ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(101))
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(102))
		return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager manager1, manager2,manager3,manager4,manager5;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(101));
		manager1.insert_back(DronesManager::DroneRecord(102));
		manager1.remove_front();
		manager1.remove_back();
		manager2.insert_front(DronesManager::DroneRecord(100));
		manager3.insert_front(DronesManager::DroneRecord(100));
		manager2.remove_front();
		manager3.remove_back();
		manager4.remove_front();
		manager5.remove_front();
		//testing remove front() and remove back()
		ASSERT_TRUE(manager1.select(0)==DronesManager::DroneRecord(101)&&manager1.size == 1)
		//testing remove front() when there's only one element
		ASSERT_TRUE(manager2.size == 0 && manager2.select(0) == DronesManager::DroneRecord(0))
	    ASSERT_TRUE(manager3.size == 0 && manager3.select(0) == DronesManager::DroneRecord(0))
	    //testing for trying to remove front() and remove back() when given a empty DronesManager
	    ASSERT_TRUE(manager4.size == 0 && manager4.remove_front())
	    ASSERT_TRUE(manager5.size == 0 && manager5.remove_back())
		return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(101));
		manager1.insert_back(DronesManager::DroneRecord(102));
		manager1.replace(0,DronesManager::DroneRecord(111));
		manager1.replace(2,DronesManager::DroneRecord(11));
		manager1.replace(1,DronesManager::DroneRecord(69));
		manager2.replace(0,DronesManager::DroneRecord(42));
		//checks replace first index
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(111))
		//checks replace empty list
		ASSERT_TRUE(manager2.select(0) == NULL)
		//checks replace middle index
		ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(69))
		//checks replace last index
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(11))
		manager1.reverse_list();
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(11))
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(111))
	    return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
	    return false;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
	    return false;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
	    DronesManager manager1;
	    int count = 0;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(101));
		manager1.insert_back(DronesManager::DroneRecord(102));
		//removing too many elements
		while(count!=5)
		{
			manager1.remove_back();
			count++;
		}
		ASSERT_TRUE(manager1.size == 0)
		//add some elements
		manager1.insert_front(DronesManager::DroneRecord(10));
		manager1.insert_back(DronesManager::DroneRecord(20));
		manager1.insert_back(DronesManager::DroneRecord(30));
		ASSERT_TRUE(manager1.size == 3)
		ASSERT_TRUE(manager1.select(2) == DronesManager::DroneRecord(30))
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(10))
		return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		return false;
	}    
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
	   	DronesManager manager1;
		int count = 0;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager1.insert_back(DronesManager::DroneRecord(101));
		manager1.insert_back(DronesManager::DroneRecord(102));
		manager1.insert_back(DronesManager::DroneRecord(103));
		manager1.insert_back(DronesManager::DroneRecord(104));
		manager1.insert_back(DronesManager::DroneRecord(105));
		manager1.insert_back(DronesManager::DroneRecord(106));
		manager1.reverse_list();
		ASSERT_TRUE(manager1.select(0) == DronesManager::DroneRecord(106))
		ASSERT_TRUE(manager1.select(1) == DronesManager::DroneRecord(105))
		while(count!=10)
		{
			manager1.remove_back();
			count++;
		}
		ASSERT_TRUE(manager1.size == 0)
		return true;
	}
};

#endif
