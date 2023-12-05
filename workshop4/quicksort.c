#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct item {
	double val1;
	double val2;
	double val3;
} Item;

void quickSort(Item** arr, int left, int right, int *calls);
int partition(Item** arr, int left, int right);
void swap(Item* a, Item* b);
void freeLoad(Item** itemsList, int num, int* calls);


int main(int argc, char *argv[]){
	
	char *filename = argv[1];
	FILE *file;
	file = fopen(filename, "r");  // read the file data
	
	int num;
	fscanf(file, "%d", &num); // the total number of items
	Item** itemsList = (Item**)malloc(num * sizeof(Item*));
	
	double data1, data2, data3;
	int i = 0;
	while(fscanf(file, "%lf %lf %lf\n", &data1, &data2, &data3) == 3) {
		Item* newItem = (Item*)malloc(sizeof(Item));  
		newItem->val1 = data1;
		newItem->val2 = data2;
		newItem->val3 = data3;
		itemsList[i] = newItem;
		i++;
    } 
	fclose(file);
	
	char *c = argv[2];
	bool isPrint = (argc > 2) && (strcmp(c, "p") == 0);	
	
	int *calls = (int*)malloc(sizeof(int));
    *calls = 0; 
	quickSort(itemsList, 0, num-1, calls);
	
	if(isPrint){
		for(int i = 0; i < num; i++){
			printf("%.4lf\t%.4lf\t%.4lf\n", itemsList[i]->val1, itemsList[i]->val2, itemsList[i]->val3);
		}
	}
	printf("%d\n", *calls);
	
	freeLoad(itemsList, num, calls);
	
}

void quickSort(Item** arr, int left, int right, int *calls){
	(*calls)++; 
	if (left < right) {
		int mid = partition(arr, left, right);
        quickSort(arr, left, mid - 1, calls);
        quickSort(arr, mid + 1, right, calls);
    }
}

int partition(Item** arr, int left, int right){
	int i = left - 1;
	double pivot = arr[right]->val2;
	
	for (int j = left; j < right; j++) {
        if (arr[j]->val2 < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void swap(Item* a, Item* b){
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void freeLoad(Item** itemsList, int num, int* calls){
	for(int i = 0; i < num; i++){
		free(itemsList[i]);
	}
	free(itemsList);
	free(calls);
}


	