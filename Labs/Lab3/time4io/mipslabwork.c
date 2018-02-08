/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
volatile int* PE = (volatile int*) 0xbf886110;
volatile int* TE = (volatile int*) 0xbf886100;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISDSET = (0xFF << 5);
  *TE &= ~(0xFF);
  *PE &= ~(0xFF);
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  if((*PE & 0xFF) == 0xFF){
    *PE &= ~(0xFF);
  }

  if(getbtns()){
    if(getbtns() & 4){
      mytime &= 0x0FFF;
      mytime |= getsw() << 12;
    }
    if(getbtns() & 2){
      mytime &= 0xF0fF;
      mytime |= getsw() << 8;
    }
    if(getbtns() & 1){
      mytime &= 0xFF0F;
      mytime |= getsw() << 4;

    }
  }
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *PE = *PE + 1;
  display_image(96, icon);
}
