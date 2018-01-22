/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  int result = 1; // assumes number is prime
  for(int i = 2; i < n/2; i++)
    if(n%i == 0) { // checks if number isn't prime
      result = 0; // sets result to 0
      break; // leaves the loop since we know it's not prime already
    }

  return result;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
