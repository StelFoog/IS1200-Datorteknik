

#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdint.h>
#include <stdbool.h>

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
    drawSprite(0,0,startScreen,128, 64);
    update();
    if(getbtns()){
      clrScr();
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
        DrawString("Mystic Fire", 0,8);
        DrawString("Slam", 64,8);
        DrawString("Wing Attack",0, 40);

        if(i % 2 ) drawSprite(64-16 + right * 64 ,8 + up * 32 , cursor, 8, 8);

        }
      }
    }
    /*
    int i = 0;
    while(1) {

        if(IFS(0) & 0x100){ // check if interrupt flag is enabled
          timeoutcount++; // Increment timeoutcount
          IFSCLR(0) = 0x100; //Reset the timeout flag
        }
        if(timeoutcount == 5){ // If timeoutcount is 10
          i++;
          if(i > 3) {
              i = 0;
          }
          timeoutcount = 0;
        }
        if(i == 0) {
            clrScr();
            drawSprite(128-32, 0, qminx.front);
        } else if(i == 1 || i == 3) {
            clrScr();
            drawSprite(128-32, 1, qminx.front);
        } else {
            clrScr();
            drawSprite(128-32, 2, qminx.front);
        }
        update();
    }

    drawSprite(0, 64-32, qminx.back);
    update();
    */
}
