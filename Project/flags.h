#ifndef HEADER_FLAGS
#define HEADER_FLAGS

typedef enum moveFlagID {
    protectID,
} moveFlagID;

char getFlag(unsigned char flagID, battlePokemon pokemon);
void setFlag(unsigned char flagID, battlePokemon *pokemon);
void clrFlag(unsigned char flagID, battlePokemon *pokemon);
void clrAllFlags(battlePokemon *pokemon);


#endif
