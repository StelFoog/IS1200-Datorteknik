#ifndef HEADER_GRAPHICS
#define HEADER_GRAPHICS

typedef struct sprite {
    const unsigned char front[128];
    const unsigned char back[128];
} sprite;

const unsigned char startScreen[1024];

const unsigned char cursor[8];

const unsigned char pkmnSelectCursor[4];

const unsigned char statusMove[32];

const unsigned char spAtkSprite[8];

const sprite seahorseSprite;
const sprite qminxSprite;
const sprite temitSprite;
const sprite nullSprite;

#endif
