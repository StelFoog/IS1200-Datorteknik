#ifndef HEADER_BATTLE
#define HEADER_BATTLE

int damageCalc(int level, char basePow, int atk, int def, double stab, double type1, double type2);
double typeEffect(type move, type opponent);
double stab(type move, type user1, type user2);
unsigned char priority(moveStruct move1, moveStruct move2, int speed1, int speed2);

#endif
