#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crack(char *salt_and_encrypted){
  int a,b,c;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

 
    for(a='A'; a<='Z'; a++){
      for(b='A'; b<='Z'; b++){
        for(c=0; c<=99; c++){
          sprintf(plain, "%c%c%02d", a, b, c); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
		//return;	//uncomment this line if you want to speed-up the running time, program will find you the cracked password only without exploring all possibilites
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
  crack("$6$AS$L/kfu7UXSULF1LlMoD4yUsBW7SpwZJHjGr2t7TWOhcQT1/i/2H6XcIIybUi.xUk4uS0JA.Y1I2Ajc0KIUwsVS/");//Copy and Paste your ecrypted password here using EncryptShA512 program// 
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &difference);
  printf("run lasted %9.5lfs\n", difference/1000000000.0);

  return 0;
}

