#ifndef HEADER_BATTLE
#define HEADER_BATTLE

unsigned int damageCalc(int level, unsigned char basePow, short atk, short def, unsigned char stab, unsigned short typeMod);
unsigned char typeEffect(type move, type opponent);
unsigned short typeMod(moveStruct move, battlePokemon pkmn);
unsigned char stab(moveStruct move, battlePokemon pkmn);
unsigned char priority(moveStruct move1, moveStruct move2, int speed1, int speed2);
void attackExec(moveStruct atackMove, battlePokemon atkPokemon, battlePokemon *defPokemon);
void battlePhase(battlePokemon *pokemon1, battlePokemon *pokemon2, moveStruct move1, moveStruct move2);

#endif
