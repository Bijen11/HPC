#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <math.h>




char *encrypted= "$6$AS$L/kfu7UXSULF1LlMoD4yUsBW7SpwZJHjGr2t7TWOhcQT1/i/2H6XcIIybUi.xUk4uS0JA.Y1I2Ajc0KIUwsVS/";  
pthread_mutex_t mutex;


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void threads()
{
pthread_mutex_init(&mutex, NULL);	
  pthread_t thread_1,thread_2;
  void *crack_A_M();
  void *crack_N_Z();
  
  pthread_create(&thread_1, NULL,(void*)crack_A_M, encrypted); 
  pthread_create(&thread_2, NULL,(void*)crack_N_Z, encrypted);
  
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);

}


void *crack_A_M(char *salt_and_encrypted){
  int a,b,c;     // Loop counters
  char salt[7];    // String used in hashing the password. 
  char plain[7];   // The combination of letters currently being checked 
  char *enc;  
   int count = 0;     // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);
  pthread_mutex_lock(&mutex);
  for(a='A'; a<='M'; a++){
    for(b='A'; b<='Z'; b++){
        for(c=0; c<=99; c++){
          sprintf(plain, "%c%c%02d", a, b, c); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
            printf("#%-8d%s %s\n", count, plain, enc);
              //return; //uncomment this line , program will find you the cracked password only without exploring all possibilites
          } 
        } 
      }
    }
    pthread_mutex_unlock(&mutex);
  }
  void *crack_N_Z(char *salt_and_encrypted){
  int a,b,c;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, 
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;  
  int count = 0;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);
  pthread_mutex_lock(&mutex);

  for(a='N'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
        for(c=0; c<=99; c++){
          sprintf(plain, "%c%c%02d", a, b, c); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
		        //return;	//uncomment this program will find you the cracked password only without exploring all possibilites
          } 
        } 
      }
    }
    pthread_mutex_unlock(&mutex);
  }

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

int main(int argc, char *argv[]){
  struct timespec start, finish;
  long long int difference;   
  clock_gettime(CLOCK_MONOTONIC, &start);
  threads();  // calling thread function 
 
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &difference);
  printf("run lasted %9.5lfs\n", difference/1000000000.0);

  return 0;
}




