// Priority queue using a linked list
#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main()
{
	Item* mypq = Initialize();

	// test cases with empty queue
	Print(mypq);
	printf("Number of flights: %d\n",Count(mypq));
	Remove(mypq);

	// test cases without errors
	int returnval;
	returnval = Add(mypq,'S',1402,2317);
	if(returnval == 1) printf("Error adding to pq\n");
	returnval = Add(mypq,'C',70,1043);
	returnval = Add(mypq,'S',201,500);
	returnval = Add(mypq,'D',1691,1601);

	printf("Number of flights: %d\n",Count(mypq));
	printf("Number of Southwest flights: %d\n",CountAirline(mypq,'S'));
	printf("Number of Delta flights: %d\n",CountAirline(mypq,'D'));

	int flighttest = 100;
	printf("Number of flight numbers smaller/larger than %d: %d, %d\n",flighttest,
		CountSmaller(mypq,flighttest),CountLarger(mypq,flighttest));

	int mypriority = 1200;
	printf("Number of flights earlier/later than %d: %d, %d\n",mypriority,
		CountEarlier(mypq,mypriority),CountLater(mypq,mypriority));

	Remove(mypq);
	Print(mypq);

	Finalize(mypq);
	free(mypq);

	return 0;
}

