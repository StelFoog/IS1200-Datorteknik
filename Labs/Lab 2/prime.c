/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  int result = 0; // assumes number isn't prime
  for(int i = 2; i < n/2; i++)
    if(n%i == 0) { // checks if it is
      result = 1; // sets result to 1
      break; // leaves the loop since we know it's prime already
    }
  
  return result;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
