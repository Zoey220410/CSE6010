#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	long int num_rand_points;
	int num_omp_threads;
	num_rand_points = atol(argv[1]);
	num_omp_threads = atoi(argv[2]);
	
	omp_set_num_threads(num_omp_threads);
	
	double start_time, end_time, elapsed_time;
	start_time = omp_get_wtime();

	long int count = 0;
	long int i;
	#pragma omp parallel
	{
		long int local_count = 0;
		unsigned int seed = (unsigned int)time(NULL) + omp_get_thread_num();
		#pragma omp for
		for(i = 0; i < num_rand_points; i++){
			double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
			
			if(x * x + y * y < 1.0){
				local_count++;
			}
		}
		
		#pragma omp atomic
		count += local_count;
	}
	
	double pi_estimate = 4.0 * (double)count / num_rand_points;	
	
	end_time = omp_get_wtime();
	
	elapsed_time = end_time - start_time;
	
	printf("%f, %f\n", pi_estimate, elapsed_time);
}