/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int numbersInRow = 0;

void printNumber(int num) {
  printf("%10d ", num);
  numbersInRow++; // increases the count
  if(numbersInRow == COLUMNS) {
    printf("\n");
    numbersInRow = 0;
  }
}

int is_prime(int n){
  int result = 1; // assumes number is prime
  for(int i = 2; i < n/2; i++)
    if(n%i == 0) { // checks if number isn't prime
      result = 0; // sets result to 0
      break; // leaves the loop since we know it's not prime already
    }
  return result;
}

void print_primes(int n){
  if(n >= 2) // checks if the number is 2 or higher
    printNumber(2); // prints the first prime
  for(int i = 3; i < n; i++) {
    if(is_prime(i)) // prints the number if it's prime
      printNumber(i);
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
