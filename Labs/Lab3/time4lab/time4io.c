#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
  int SW = (PORTD >> 8) & 0xF;
  return SW;
}

int getbtns(void){
  int btns = (PORTD >> 5) & 0x7;
  return btns;
}
