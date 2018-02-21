#ifndef HEADER_BATTLE
#define HEADER_BATTLE

unsigned int damageCalc(unsigned char level, unsigned char basePow, unsigned short atk, unsigned short def, unsigned char stab, unsigned short typeMod);
unsigned char typeEffect(type * move, type * opponent);
unsigned short typeMod(moveStruct * move, battlePokemon * pkmn);
unsigned char stab(moveStruct * move, battlePokemon * pkmn);
unsigned char priority(moveStruct * move1, moveStruct * move2, battlePokemon * pokemon1, battlePokemon * pokemon2);
double getStageBuff(signed char stage);
void setStageBuff(signed char *stage, signed char increaseDecrease);
void attackExec(moveStruct *move, battlePokemon *atkPokemon, battlePokemon *defPokemon);
void battlePhase(battlePokemon *pokemon1, battlePokemon *pokemon2, moveStruct *move1, moveStruct *move2);

#endif
