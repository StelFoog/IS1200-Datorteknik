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

int prime = 1234567;
int mytime = 0x5957;
volatile int* PE = (volatile int*) 0xbf886110;
volatile int* TE = (volatile int*) 0xbf886100;

char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0; // Declare timeoutcount
/* Interrupt Service Routine */
void user_isr( void ) {
  if(IFS(0) & 0x8000) {
    (*PE)++;
    if((*PE)>=0x100) {
      (*PE) &= ~(0xff);
    }
    IFSCLR(0) = 0x8000;
  } else {
    timeoutcount++;
    if(timeoutcount == 10){
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      timeoutcount = 0;
    }
    IFSCLR(0) = 0x100;    // Clear flag
  }
}


/* Lab-specific initialization goes here */
void labinit( void )
{
  PR2 = (80000000 / 256) / 10;  //Set period to 1/10 of a second
  T2CON = 0x0; //Clearing clock
  T2CONSET = 0x70;              //Set prescale to 256
  TMR2 = 0;                     //Reset timer
  T2CONSET = (1 << 15);            // turn timer on

  TRISDSET = (0xFF << 5);       //Set port D for input
  *TE &= ~(0xFF);               //Set port E for output
  *PE &= ~(0xFF);               //Reset the LED bits

  IPC(2) = IPC(2) | 0x10;
  // Enable interrupt for timer2
  IECSET(0) = 0x100;
  IECSET(0) = 0x8000;
  //Set priority for external interrupt 3
  IPC(3) = IPC(3) | (0x1 << 26);
  //IPC(3) = IPC(3) | (0x4);
  INTCONSET = 0x8;
  IFSCLR(0) = 0x8100;
  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();
}
