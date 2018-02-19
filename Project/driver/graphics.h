/*const unsigned char logo[];
const unsigned char mice[];
const unsigned char MysticFire[];*/
#ifndef GRAPHICS_HEADER
#define  GRAPHICS_HEADER

typedef struct sprite {
    const unsigned char front[128];
    const unsigned char back[128];
} sprite;

const unsigned char startScreen[1024];

const unsigned char cursor[8];

const sprite qminx;

#endif
