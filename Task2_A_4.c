#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int time_difference(struct timespec *start, struct timespec *finish, 
                              long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main()
{
	 struct timespec start, finish;
  	long long int difference;  
	int Value;
	int blockSize = 100;
	printf("\nEnter size of Matrix\n");
	scanf("%d", &Value);
	
	
	//int SizeOfArray = *Value;
	int a[Value][Value], b[Value][Value], c[Value][Value],temp ;
	int i, j, k;
	//printf("\nEnter Firt Matrix\n");
	for(i=0; i<Value; i++) {
	 for(j=0; j<Value; j++) {
	  a[i][j]=rand() % 200;
	 
	  }
	 
	}
	
	//printf("Enter the Second Matrix\n");
	printf("valee "); 
	for(i=0; i<Value; i++) {
	 for(j=0; j<Value; j++) {
	  b[i][j]=rand() % 200;
	
	 }

	}
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0; i<Value; i++) {
	for(k=0 ;k< Value; k++){

	temp=a[i][k];
		c[i][j]=0;
		for(j = 0; j< Value; j++){
			c[i][j]+= temp* b[k][j];
		
			
		
			
		}
		
		
	
	}
	
	
	 
	}
	printf("\nThe results is…\n");
	for(i=0; i<Value; i++) {
	 for(j=0; j<Value; j++) {
	   printf("%d  ", c[i][j]); 
	  }
	printf("\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
  	time_difference(&start, &finish, &difference);
  	printf("run lasted %9.5lfs\n", difference/1000000000.0);
	return 0;
}

