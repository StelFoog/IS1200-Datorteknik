#ifndef HEADER_MAIN
#define HEADER_MAIN

#define MOVEAMOUNT 3

typedef enum type{          null,
    normal,     fire,       water,      grass,
    ground,     flying,     ice,        electric,
} type;

typedef struct moveStruct {
    char name[20];
    type attackType;
    unsigned char power;
    unsigned char accuracy;
    unsigned char phySpecPrio;
}  moveStruct;

typedef struct pokemonStruct{
    char name[15];
    type pokemonType1;
    type pokemonType2;
    moveStruct moveset[MOVEAMOUNT];
    unsigned char baseHp;
    unsigned char baseSpeed;
    unsigned char basePyAtk;
    unsigned char basePyDef;
    unsigned char baseSpAtk;
    unsigned char baseSpDef;
} pokemonStruct;

typedef struct battlePokemon{
    char name[16];
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
} battlePokemon;



#endif
