

#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h>
#include <stdbool.h>

#include "OLED_I2C.h"
#include "graphics.h"

int timeoutcount = 0;

int getbtns(void){
  return (PORTD >> 5) & 0x7;
}

void init(){
  T2CONSET = 0x70;              //Set prescale to 256
  PR2 = (80000000 / 256) / 10;  //Set period to 1/10 of a second
  TMR2 = 0;                     //Reset timer
  T2CONSET = 0x8000;            // turn timer on
  TRISDSET = (0x7 << 5);       //Set port D for input
  begin();
  drawSprite(0,0,startScreen,128, 64);
  update();
}

char battleSelect(){
  char cursorBlink, down, right, buttonCheck = 1, selected = 0;
  while(1){
    update();
    if(getbtns() && buttonCheck){
      buttonCheck = 0;
      if(getbtns() & 0x1) selected += 1;
      if(getbtns() & 0x2) selected -= 1;
      if(getbtns() && 0x4) return selected;
    }
    if(selected > 3) selected = 0;
    else if(selected < 0) selected = 3;

    if(selected > 1) down = 1;
    else down = 0;

    if(selected % 2) right = 1;
    else right = 0;

    if(IFS(0) & 0x100){         // check if interrupt flag is enabled
      timeoutcount++;           // Increment timeoutcount
      IFSCLR(0) = 0x100;        //Reset the timeout flag
    }
    if(timeoutcount == 5){      // If timeoutcount is 10
      buttonCheck = 1;
      cursorBlink++;
      timeoutcount = 0;
    }
    clrScr();
    DrawString("Mystic Fire", 0,8);
    DrawString("Slam", 64,8);
    DrawString("Wing Attack",0, 40);
    if(cursorBlink % 2 ) drawSprite(64-16 + right * 64 , 8 + down * 32 , cursor, 8, 8);
  }
}

int main(void){
  init();
  while(1){
    if(getbtns()){
      clrScr();
      char selected move  = battleSelect();
    }
  }
}
