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

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  T2CONSET = 0x70;              //Set prescale to 256
  PR2 = (80000000 / 256) / 10;  //Set period to 1/10 of a second
  TMR2 = 0;                     //Reset timer
  T2CONSET = 0x8000;            // turn timer on

  TRISDSET = (0xFF << 5);       //Set port D for input
  *TE &= ~(0xFF);               //Set port E for output
  *PE &= ~(0xFF);               //Reset the LED bits
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  if((*PE & 0xFF) == 0xFF){ // Check if all LEDs are lit
    *PE &= ~(0xFF); // Reset LEDs
  }
  if(getbtns()){ // Check if any buttons are pressed
    if(getbtns() & 4){ // If the 3rd (4th) button is pressed
      mytime &= 0x0FFF; // Clear first digit
      mytime |= getsw() << 12; // Place the value of the switches as the first digit
    }
    if(getbtns() & 2){
      mytime &= 0xF0FF;
      mytime |= getsw() << 8;
    }
    if(getbtns() & 1){
      mytime &= 0xFF0F;
      mytime |= getsw() << 4;
    }
  }
  *PE = *PE + 1;
  //delay( 1000 );
  if(IFS(0) & 0x100){ // check if interrupt flag is enabled
     timeoutcount++; // Increment timeoutcount
    IFSCLR(0) = 0x100; //Reset the timeout flag
  }
  if(timeoutcount == 10){ // If timeoutcount is 10
    time2string( textstring, mytime ); //
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeoutcount = 0; // reset count
  }
  display_image(96, icon);
}
