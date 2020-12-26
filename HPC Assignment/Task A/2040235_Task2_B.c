#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAT_SIZE 1024

int i,j,k;           //Parameters For Rows And Columns
int matrix1[MAT_SIZE][MAT_SIZE]; //First Matrix
int matrix2[MAT_SIZE][MAT_SIZE]; //Second Matrix
int result [MAT_SIZE][MAT_SIZE]; //Multiplied Matrix

//Type Defining For Passing Function Argumnents
typedef struct parameters {
    int x,y;
}args;

//Function For Calculate Each Element in Result Matrix Used By Threads - - -//
void* mulMatt(void* arg){
    
    args* p = arg;
    
    //Calculating Each Element in Result Matrix Using Passed Arguments
    for(int a=0;a<j;a++){
        result[p->x][p->y] += matrix1[p->x][a]*matrix2[a][p->y];
    }
    sleep(3);
    
    //End Of Thread
    pthread_exit(0);
}


int main(){
    int x,y;        
    int MAX_THREADS;
	printf("\nEnter size of MAX_THREADS\n");
	scanf("%d", &MAX_THREADS);
    //Initializing All Defined Matrices By Zero - - - - - - - - - - - - - - -//
    for(int x=0;x<1024;x++){
        for(int y=0;y<1024;y++){
            matrix1[x][y] =0;
            matrix2[x][y] =0;
            result[x][y] = 0;
        }
    }
    
    
    //Getting Matrix1 And Matrix2 Info from User - - - - - - - - - - - - - - -//
    

    
    // Getting Row And Column(Same As Row In Matrix2) Number For Matrix1
    printf("Enter number of rows for matrix 1: ");
    scanf("%d",&i);
    printf("Enter number of columns for matrix 1: ");
    scanf("%d",&j);
    
    printf("\n --- Initializing Matrix 1 ---\n\n");
    for(int x=0;x<i;x++){
        for(int y=0;y<j;y++){
            matrix1[x][y] =rand()%50;
        }
    }
    


    // Getting Column Number For Matrix2
    printf("Number of rows for matrix 2 : %d\n",j);
    printf("Enter number of columns for matrix 2: ");
    scanf("%d",&k);
    
    printf("\n --- Initializing Matrix 2 ---\n\n");
    for(int x=0;x<j;x++){
        for(int y=0;y<k;y++){
            matrix2[x][y]=rand()%50;
        }
    }
    
    
  
    

    
    //Defining Threads
    pthread_t thread[MAX_THREADS];
    
    //Counter For Thread Index
    int thread_number = 0;
    
    //Defining p For Passing Parameters To Function As Struct
    args p[i*k];
    
    //Start Timer
    time_t start = time(NULL);
    
    for(int x=0;x<i;x++){
        for(int y=0;y<k;y++){
            
            //Initializing Parameters For Passing To Function
            p[thread_number].x=x;
            p[thread_number].y=y;
            
            //Status For Checking Errors
            int status;
            
            //Create Specific Thread For Each Element In Result Matrix
            status = pthread_create(&thread[thread_number], NULL, mulMatt, (void *) &p[thread_number]);
            
            //Check For Error
            if(status!=0){
                printf("Error In Threads");
                exit(0);
            }
            
            thread_number++;
        }
    }
    
    
    //Wait For All Threads Done - - - - - - - - - - - - - - - - - - - - - - //
    
    for(int z=0;z<(i*k);z++)
        pthread_join(thread[z],NULL );
    
    
    //Print Multiplied Matrix (Result) - - - - - - - - - - - - - - - - - - -//
    
    printf(" --- Multiplied Matrix ---\n\n");
    for(int x=0;x<i;x++){
        for(int y=0;y<k;y++){
            printf("%5d",result[x][y]);
        }
        printf("\n\n");
    }
    
    
    //Calculate Total Time Including 3 Soconds Sleep In Each Thread - - - -//
    
    printf(" ---> Time Elapsed : %.2f Sec\n\n", (double)(time(NULL) - start));
    
    
    //Total Threads Used In Process - - - - - - - - - - - - - - - - - - - -//
    
    printf(" ---> Used Threads : %d \n\n",thread_number);
    for(int z=0;z<thread_number;z++)
        printf(" - Thread %d ID : %d\n",z+1,(int)thread[z]);
    for(y=10;y>=-10;y--)
          {
               for(x=start;x<=time(NULL)-1;x++)
                  {
                        if(y==(double)(time(NULL) - start))
                            {
                                printf("* ");
                            }
                        else
                           {
                               printf("  ");
                           }
                  }printf("\n");
          }
    return 0;
}

