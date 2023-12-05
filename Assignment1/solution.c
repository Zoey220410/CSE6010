#include <stdio.h>
#include <math.h>
#define ITERATION_MAX 50

/*
status:
    0: success
    1: max iterations reached
    2: singular jacobian
    3: negative in sqrt
    4: not implemented
*/

void newton_method(double x0, double y0, double* x, double* y, int* iterations, int* status) {
    *x = x0;
    *y = y0;
    *iterations = 0;
    *status = 4;
	double f,g,x_delta,y_delta,jacobian;
	
	for (*iterations = 1; *iterations < ITERATION_MAX + 1; (*iterations)++){ //limit interation less than 50
		jacobian = 2 * (*x) * 42 * (*y) - 2 * (*y) * 10 * (*x); //calculate Jacobian determinant to check whether it is a singular jacobian
		if(jacobian == 0){
			*status = 2;
			return;  //stop iteration
		}
		
		f = (*x) * (*x) + (*y) * (*y) - 1;   //calculate intermediate variables
		g = 5 * (*x) * (*x) + 21 * (*y) * (*y) - 9;
		
		x_delta = - (1/jacobian) * (42 * (*y) * f + (-2) * (*y) * g);  //calculate the change of the results by iteration
		y_delta = - (1/jacobian) * ((-10) * (*x) * f + 2 * (*x) * g);
		
		if(fabs(x_delta) < 1e-10 && fabs(y_delta) < 1e-10){  //check whether it converges successfully
			*status = 0;
			return;  //stop iteration
		}
		
		*x = *x + x_delta; //update results
		*y = *y + y_delta;
	}

	*status = 1;
	(*iterations)--;
	return;  // finish iteration
}

void fixed_point_iteration(double x0, double y0, double* x, double* y, int* iterations, int* status) {
    *x = x0;
    *y = y0;
    *iterations = 0;
    *status = 4;
	double x1, y1;
	
	for (*iterations = 1; *iterations < ITERATION_MAX + 1; (*iterations)++){ //limit interation less than 50
		if(1 - (*y) * (*y) < 0 || 9 - 5 * (*x) * (*x) < 0){ //check whether it is a negative number
			*status = 3;
			return;
		}
		x1 = sqrt(1 - (*y) * (*y));
		y1 = (1 / sqrt(21)) * sqrt(9 - 5 * (*x) * (*x));
		
		if(fabs(x1 - *x) < 1e-10 && fabs(y1 - *y) < 1e-10){  //check whether it converges successfully
			*status = 0;
			return;  //stop iteration
		}
		
		*x = x1; //update results
		*y = y1;
	}
	
	*status = 1;
	(*iterations)--;
	return;  // finish iteration
		
}
