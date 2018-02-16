/*const unsigned char logo[];
const unsigned char mice[];
const unsigned char MysticFire[];*/
#ifndef GRAPHICS_HEADER
#define  GRAPHICS_HEADER

typedef struct word {
  int width;
  int height;
  unsigned char data[8*2*6];
} word;

typedef struct sprite {
    unsigned char front[128];
    unsigned char back[128];
} sprite;


const word cursor;

const word MysticFire;
const word Slam;
const word WingAttack;
const sprite qminx;

#endif
