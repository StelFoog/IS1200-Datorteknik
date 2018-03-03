#ifndef HEADER_MAIN
#define HEADER_MAIN

#define POKEMON_COUNT 6
#define MOVEAMOUNT 4 // amount of moves in a moveset

#include "driver/graphics.h"
    // all types
typedef enum type{ null,
    normal,     fire,       water,      grass,
    ground,     flying,     ice,        electric,
} type;

    // struct for all moves
typedef struct moveStruct {
    unsigned char moveEffectID;
    type attackType;
    unsigned char power;
    unsigned char accuracy;
    unsigned char phySpecPrio;
    char name[16];
}  moveStruct; // size of moveStruct is 24 byte

    // struct for all possible to choose from pokemon
typedef struct pokemonStruct{
    char name[12];
    type pokemonType1;
    type pokemonType2;
    moveStruct moveset[MOVEAMOUNT];
    unsigned char baseHp;
    unsigned char baseSpeed;
    unsigned char basePyAtk;
    unsigned char basePyDef;
    unsigned char baseSpAtk;
    unsigned char baseSpDef;
    const sprite *sprite;
} pokemonStruct; // size of pokemonStruct is 104 byte

    // struct for the two pokemon in battle
typedef struct battlePokemon{
    type pokemonType1;
    type pokemonType2;
    moveStruct moveset[MOVEAMOUNT];
    unsigned char level;
    unsigned short hp;
    unsigned short speed;
    unsigned short pyAtk;
    unsigned short pyDef;
    unsigned short spAtk;
    unsigned short spDef;
    signed char speedStage;
    signed char pyAtkStage;
    signed char pyDefStage;
    signed char spAtkStage;
    signed char spDefStage;
    unsigned char flag;
    const sprite *sprite;
} battlePokemon; // size of battlePokemon is 112 byte

char * hpString(char str[], unsigned short hp, unsigned char curleng);

#endif
