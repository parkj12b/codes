#include "lab3_priority_queue.hpp"
//Jacob Park ID:20857120
//Mark Baula ID:20823953
using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	heap = new TaskItem*[n_capacity + 1];
	capacity = n_capacity;
	size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for(int i = 1; i < size; ++i)
	{
		delete heap[i];
		heap[i] = NULL;
	}
	delete []heap;
	heap = NULL;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	return (size == 0);
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return (size == capacity);		
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for(int index = 1; index < size; index++)
	{
		cout << heap[index]->priority << "     " << heap[index]->description << endl;
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if(size == 0)
		return TaskItem(-1, "NULL");
	else
		return *heap[1];
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if(size == capacity)
		return false; 
	else if (size == 0)
	{
		TaskItem* _val = new TaskItem(val);
		heap[1] = _val;
	}
	else{
		int i = size + 1;
		heap[i] = new TaskItem(val);
		while (i > 1 && heap[i / 2]->priority < heap[i]->priority) 
		{
			TaskItem* temp = heap[i];
			heap[i] = heap[i / 2];
			heap[i / 2] = temp;
			i = i / 2;
		}
	}
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if(size == 0)
		return false;
	else if(size == 1)
	{
		delete heap[1];
		heap[1] = NULL;
		size --;
		return true;
	}
	else {
		delete heap[1];
		heap[1] = heap[size];
		heap[size] = NULL;
		size--;
		int i = 1;
		while(i*2+1 <= size)
		{
			//check if left node is bigger than right && also bigger than parent
			if(heap[i*2]->priority >= heap[i*2+1]->priority && heap[i*2]->priority > heap[i]->priority)
			{
				TaskItem* temp = heap[i];
				heap[i] = heap[i*2];
				heap[i*2] = temp;
				i *= 2;
				
			}
			//check if right node is bigger than left && also bigger than parent
			else if(heap[i*2+1]->priority >= heap[i*2]->priority && heap[i*2+1]->priority > heap[i]->priority)
			{
				TaskItem* temp = heap[i];
				heap[i] = heap[i*2+1];
				heap[i*2+1] = temp;
				i = i*2+1;
			}
		}
		//consider case when the heap only has a single node at the end than do the same swap thing
		if(i*2 == size && heap[2*i]->priority > heap[i]->priority)
		{
			TaskItem*temp = heap[i];
			heap[i] = heap[i*2];
			heap[i*2] = temp;
			i *= 2;
		}
	}
	return true;
}
