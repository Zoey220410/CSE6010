#include <stdio.h>
#include<stdlib.h>

struct Node{   // linkedlist node
	int value;
	struct Node* next;
};

struct Node* nodeCreate(int num){
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));   // allocate memory for the new code
	if (newNode == NULL) {
		printf("Error in allocating the data array.\n");
		exit(1);
	}
	newNode->value = num;
	newNode->next = NULL;
	return newNode;
}

	

void linkInsert(struct Node* dummyHead, int num){
	struct Node* newNode = nodeCreate(num);   // create a new node
	if(dummyHead->next == NULL){
		dummyHead->next = newNode;  // insert the first element
	}
	else{
		newNode->next = dummyHead->next;   // insert element from the beginning
		dummyHead->next = newNode;
	}

}

void linkPrint(struct Node* dummyHead){
	struct Node* cur = dummyHead->next;  // output from the first element
	while(cur != NULL){
		printf("%d ", cur->value);
		cur = cur->next;
	}
	printf("\n");
}

void freeload(struct Node* dummyHead){
	struct Node* cur = dummyHead;
	struct Node* temp;
	while(cur != NULL){
		temp = cur->next;
		free(cur);
		cur = temp;
	}
}

int main(){
	struct Node* dummyHead = nodeCreate(-1);
	for(int i = 0; i < 10; i++){
		linkInsert(dummyHead, i);  // insert element to the linkedlist
	}
	
	linkPrint(dummyHead);  // output linkedlist element
	freeload(dummyHead);  // free memory
	
	return 0 ;
}


