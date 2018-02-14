#ifndef HEADER_MAIN
#define HEADER_MAIN

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
    moveStruct moveset[3];
    unsigned char baseHp;
    unsigned char baseSpeed;
    unsigned char baseAtk;
    unsigned char baseDef;
    unsigned char baseSAtk;
    unsigned char baseSDef;
} pokemonStruct;

typedef struct battlePokemon{
    char name[16];
    type pokemonType1;
    type pokemonType2;
    moveStruct moveset[3];
    unsigned char level;
    unsigned int hpSpeed;
    unsigned int pyAtkDef;
    unsigned int spAtkDef;
} battlePokemon;



#endif
