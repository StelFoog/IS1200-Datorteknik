/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_primes(int n){
  int countPrime = 0;
  if(n >= 2) { // checks if the number is 2 or higher
    printf("%10d ", 2); // prints the first prime number
    countPrime++; // starts counting the primes
  }
  int isPrime;
  for(int i = 3; i < n; i++) {
    isPrime = 1; // assumes the number is a prime
    for(int j = 2; j <= i/2; j++) {
      if(i%j == 0) { // checks if it's divisable
        isPrime = 0; // says number isn't prime
        break; // leaves the loop since we know it's not prime already
      }
    }
    if(isPrime) { // prints the number if it's prime
      printf("%10d ", i);
      countPrime++; // increases the count
      if(countPrime == COLUMNS) { // checks if the primes has filles the row
        printf("\n"); // starts a new row of primes
        countPrime = 0; // resets the count
      }
    }
  }

  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1])); // atoi converts the argument to an int
  else
    printf("Please state an interger number.\n");
  return 0;
}
