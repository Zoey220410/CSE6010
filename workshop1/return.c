#include <stdio.h>
#include <math.h>

void method1(double arr[], double *value, int *index){
	*value = arr[0];
	*index = 0;
	for(int i = 1; i < 100; i++){
		if(arr[i] > *value){ // update the values at the addresses
			*value = arr[i];
			*index = i;
		}
	}
	return;
}

double method2(double arr[], int *index){
	double value = arr[0];
	*index = 0;
	for(int i = 0; i < 100; i++){
		if(arr[i] > value){  
			value = arr[i];  // update value
			*index = i;  // update the values at the address
		}
	}
	return value;    //  return the maximum value
}


struct ValueMax3{
	double value;
	int index3;
};

struct ValueMax3 method3(double arr[])
{
	struct ValueMax3 res;
	res.value = arr[0];
	res.index3 = 0;
	
	for(int i = 1; i < 100; i++){
		if(arr[i] > res.value){  // update struct
			res.value = arr[i];
			res.index3 = i;
		}
	}	
	return res;  // return the result struct
}

int main(){
	double array[100], valueMax1, valueMax2;
	int valueIndex1, valueIndex2;
	for(int i = 0; i < 100; i++){
		array[i] = 1 + sin(i);
	}
	
	method1(array, &valueMax1, &valueIndex1);  // pass both maximum value and the corresponding index addresses
	printf("max: %lf, index: %d\n", valueMax1, valueIndex1);
	
	valueMax2 = method2(array, &valueIndex2);  // only pass the corresponding index address
	printf("max: %lf, index: %d\n", valueMax2, valueIndex2);
	
	struct ValueMax3 result = method3(array);
	printf("max: %lf, index: %d\n", result.value, result.index3);
	
	return 0;
}



