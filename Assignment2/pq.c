// Typedef and function definitions for PQ
#include <stdio.h>
#include <stdlib.h>

typedef struct flightinfo {
	char airline; 		// use U for United, D for Delta, A for American, S for Southwest
	int flightnumber;
	int time;
} Flightinfo;

typedef struct item {
	Flightinfo flight;
	int* priority; // priority is a pointer to an int, will point to flighttime
	struct item * next;
} Item;

Item* Initialize()
{
	Item* dummyHead = (Item*) malloc(sizeof(Item)); // create a dummy node that points to PQ
	if (dummyHead == NULL) return NULL;
	
	dummyHead->flight.airline = ' ';
	dummyHead->flight.flightnumber = -1;
	dummyHead->flight.time = -1;
	
	dummyHead->priority = &(dummyHead -> flight.time);
	
	dummyHead->next = NULL;
	
	return dummyHead;
}

int Add(Item* mypq, char itemAirline, int itemFlightnumber, int itemTime)
{
	if(itemFlightnumber < 0 || itemTime < 0) return 1;  // error case
	
	Item* newNode = (Item*) malloc(sizeof(Item)); // Create a new node
	if (newNode == NULL) return 1;
	
	newNode->flight.airline = itemAirline;
	newNode->flight.flightnumber = itemFlightnumber;
	newNode->flight.time = itemTime;
	
	Item* cur = mypq->next;
	/*Compare flighttime and set the new node into the right position.*/
	if (!cur || itemTime < cur->flight.time){
		newNode->next = cur;
		mypq->next = newNode;
	}
	else{
		while(cur->next && cur->next->flight.time < itemTime){
			cur = cur->next;
		}
		 newNode->next = cur->next; 
		 cur->next = newNode;
	}
	
	return 0;
}

void Remove(Item* mypq)
{
	if(!mypq->next) return; // PQ is empty.
	Item* temp = mypq->next->next;
	free(mypq->next); // delete the first node in the PQ
	mypq->next = temp;
	
}

void Print(Item* mypq)
{
	Item* temp = mypq->next;
	printf("Priority queue contents:\n");
	while(temp){
		printf("%c %d %d\n",temp->flight.airline, 
		temp->flight.flightnumber, temp->flight.time);
		temp = temp->next;
	}
}

int Count(Item* mypq)
{
	Item* temp = mypq->next;
	int count = 0; 
	while(temp){
		count++;
		temp = temp->next;
	}
	return count; // if PQ is empty, return 0
}

int CountAirline(Item* mypq, char myairline)
{
	Item* temp = mypq->next;
	int count = 0;
	while(temp){
		if(temp->flight.airline == myairline){
			count++;	
		}
		temp = temp->next;
	}
	return count;
}

int CountSmaller(Item* mypq, int itemflightnumber)
{
	Item* temp = mypq->next;
	int count = 0;
	while(temp){ // traverse all the nodes
		if(temp->flight.flightnumber < itemflightnumber){
			count++;	
		}
		temp = temp->next; 
	}
	return count;
}

int CountLarger(Item* mypq, int itemflightnumber)
{
	Item* temp = mypq->next;
	int count = 0;
	while(temp){ // traverse all the nodes
		if(temp->flight.flightnumber > itemflightnumber){
			count++;	
		}
		temp = temp->next; 
	}
	return count;
}

int CountEarlier(Item* mypq, int mypriority)
{
	Item* temp = mypq->next;
	int count = 0;
	while(temp){
		if(temp->flight.time >= mypriority){
			return count; // the time is sorted, so only the node before it fulfill the requirement
		}
		count++;
		temp = temp->next;
	}
	return count;
}

int CountLater(Item* mypq, int mypriority)
{
	Item* temp = mypq->next;
	int count = 0;
	while(temp){
		if(temp->flight.time > mypriority){
			return Count(mypq)-count; // the time is sorted, the rest of nodes are all later than mypriority
		}
		count++;
		temp = temp->next;
	}
	return 0;
}

void Finalize(Item* mypq)
{
	Item* cur = mypq->next; // only free the valid node
	while(cur){
		Item* temp = cur->next;
		free(cur);
		cur = temp;
	}
}


