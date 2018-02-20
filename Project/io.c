#include <pic32mx.h>
#include "driver/graphics.h"
#include "driver/OLED_I2C.h"
#include "io.h"

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

int getBtns(void){
  return (PORTD >> 5) & 0x7;
}
