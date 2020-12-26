#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>



int count=0;     // A counter used to track the number of combinations explored so far



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crack(char *salt_and_encrypted){
  int a,b,c,d;     // Loop counters
  char salt[7];    // String used in hashing the password. 
  char plain[7];   // The combination of letters currently being checked 
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
      for(c='A'; c<='Z'; c++){
        for(d=0; d<=99; d++){
          sprintf(plain, "%c%c%c%02d", a, b, c, d); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
		//return;	//uncomment this line , program will find you the cracked password only without exploring all possibilites
          } 
        } 
      }
    }
  }
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
  crack("$6$AS$zNmgGxW0KU9n9UoRX2cuGAUjlTOi7hs0oDYW.KB3AuxCP5FF7xB2W1Z6babChq7H.gbYSGTfVA35D9OFt1tO9.");//Copy and Paste your ecrypted password 
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &difference);
  printf("run lasted %9.5lfs\n", difference/1000000000.0);

  return 0;
}

