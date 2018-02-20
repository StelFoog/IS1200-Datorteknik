#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "flags.h"

char getFlag(unsigned char flagID, battlePokemon pokemon) {
    return (pokemon.flag >> flagID) & 0x1;
}

void setFlag(unsigned char flagID, battlePokemon *pokemon) {
    (*pokemon).flag |= (1 << flagID);
}

void clrFlag(unsigned char flagID, battlePokemon *pokemon) {
    (*pokemon).flag &= ~(1 << flagID);
}

void clrAllFlags(battlePokemon *pokemon) {
    (*pokemon).flag = 0;
}
