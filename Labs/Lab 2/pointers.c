


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1[20], list2[20]; // 20 since an int is 4 bytes in size, 80/4 = 20
int count = 0;

void copycodes(char *a0, int *a1) {
  while(*a0 != '\0') { // runs until string is finished
    *a1 = *a0; // puts data in a0 in a1
    a0++; // increases adress value of a0 by one
    a1++; // increases adress value of a1 by four
    count++; // increases count by one
  }
}

void work() {
  copycodes(text1, list1); // executes copycodes with text1 and list1
  copycodes(text2, list2); // executes copycodes with text2 and list2
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));

}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
