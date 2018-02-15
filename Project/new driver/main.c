

#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h>
#include <stdbool.h>

#define charWidth		6
#define charHeight		8

#include "OLED_I2C.h"
#include "graphics.h"

int timeoutcount = 0;

int getbtns(void){
  int btns = (PORTD >> 5) & 0x7;
  return btns;
}

void init(){
  T2CONSET = 0x70;              //Set prescale to 256
  PR2 = (80000000 / 256) / 10;  //Set period to 1/10 of a second
  TMR2 = 0;                     //Reset timer
  T2CONSET = 0x8000;            // turn timer on

  TRISDSET = (0x7 << 5);       //Set port D for input
  begin();
}
int main(void){
  init();
  int i, up, right;
  char peter = 1;
  char button = 0;
  while(1){
    update();
    if(getbtns() && peter){
      peter = 0;
      if(getbtns() & 0x1){
          button += 1;
      }
      if(getbtns() & 0x2) {
          button -= 1;
      }
    }
    if(button >= 4){
      button = 0;
    } else if(button < 0) {
      button = 3;
    }
    if(button > 1){
      up = 1;
    } else up = 0;
    if(button % 2){
      right = 1;
    } else right = 0;

    if(IFS(0) & 0x100){ // check if interrupt flag is enabled
      timeoutcount++; // Increment timeoutcount
      IFSCLR(0) = 0x100; //Reset the timeout flag
    }
    if(timeoutcount == 5){ // If timeoutcount is 10
      peter = 1;
      i++;
      timeoutcount = 0;
    }
    clrScr();
    drawBitmap(0,8, MysticFire.data, charWidth * MysticFire.width, charHeight * MysticFire.height);
    drawBitmap(64, 8, Slam.data, charWidth*Slam.width, charHeight * Slam.height);
    drawBitmap(0, 32 + 8, WingAttack.data, charWidth * WingAttack.width, charHeight * WingAttack.height);

    if(i % 2 ) drawBitmap(64-16 + right * 64 ,8 + up * 32 , cursor.data, cursor.width, cursor.height);
  }
}
