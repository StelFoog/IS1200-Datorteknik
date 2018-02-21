/*const unsigned char logo[];
const unsigned char mice[];
const unsigned char MysticFire[];*/
#ifndef HEADER_GRAPHICS
#define HEADER_GRAPHICS

typedef struct sprite {
    const unsigned char front[128];
    const unsigned char back[128];
} sprite;

const unsigned char startScreen[1024];

const unsigned char cursor[8];

const unsigned char pkmnSelectCursor[4];

const sprite qminxSprite;
const sprite temitSprite;

#endif
