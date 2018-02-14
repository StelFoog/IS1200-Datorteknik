#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "battle.h"

unsigned int damageCalc(int level, char basePow, int atk, int def, double stab, double type1, double type2) {
    double result = ((((level * 2 / 5 + 2) * basePow * (atk / def) / 50) + 2) * stab * type1 * type2);
    return ((int) ceil(result));
}

double typeEffect(type move, type opponent) {
    double result;
    switch(move) {
        case fire:
            switch(opponent) {
                case fire:
                    result = 0.5;
                    break;
                case water:
                    result = 0.5;
                    break;
                case grass:
                    result = 2;
                    break;
                case ground:
                    result = 0.5;
                    break;
                case ice:
                    result = 2;
                    break;
                default:
                    result = 1;
            }
            break;
        case water:
            switch(opponent) {
                case fire:
                    result = 0.5;
                    break;
                case water:
                    result = 0.5;
                case grass:
                    result = 2;
                    break;
                case ground:
                    result = 2;
                    break;
                case ice:
                    result = 0.5;
                    break;
                default:
                    result = 1;
            }
            break;
        case grass:
            switch(opponent) {
                case fire:
                    result = 0.5;
                    break;
                case water:
                    result = 2;
                    break;
                case grass:
                    result = 0.5;
                    break;
                case ground:
                    result = 2;
                    break;
                case ice:
                    result = 0.5;
                    break;
                case flying:
                    result = 0.5;
                    break;
                default:
                    result = 1;
            }
            break;
        case ground:
            switch(opponent) {
                case fire:
                    result = 2;
                    break;
                case grass:
                    result = 0.5;
                    break;
                case flying:
                    result = 0;
                    break;
                case electric:
                    result = 2;
                    break;
                default:
                    result = 1;
            }
            break;
        case flying:
            switch(opponent) {
                case grass:
                    result = 2;
                    break;
                case ice:
                    result = 0.5;
                    break;
                case electric:
                    result = 0.5;
                    break;
                default:
                    result = 1;
            }
            break;
        case ice:
            switch(opponent) {
                case fire:
                    result = 0.5;
                    break;
                case water:
                    result = 0.5;
                    break;
                case grass:
                    result = 2;
                    break;
                case ground:
                    result = 2;
                    break;
                default:
                    result = 1;
            }
            break;
        case electric:
            switch(opponent) {
                case water:
                    result = 2;
                    break;
                case grass:
                    result = 0.5;
                    break;
                case ground:
                    result = 0;
                    break;
                case flying:
                    result = 2;
                    break;
                case electric:
                    result = 0.5;
                    break;
                default:
                    result = 1;
            }
            break;
        default:
            result = 1;
    }
    return result;
}

double stab(type move, type user1, type user2) {
    double result = 1;
    if(move == user1 || move == user2) {
        result = 1.5;
    }
    return result;
}

unsigned char priority(moveStruct move1, moveStruct move2, int speed1, int speed2) {
    unsigned char retval = 0;
    if((move1.phySpecPrio & 0x0f) < (move2.phySpecPrio & 0x0f)) {
        retval = 1;
    } else if((move1.phySpecPrio & 0x0f) == (move2.phySpecPrio & 0x0f)) {
        if(speed1 < speed2) {
            retval = 1;
        }
    }
    return retval;
}

void battlePhase(battlePokemon *pokemon1, battlePokemon *pokemon2, moveStruct move1, moveStruct move2) {
    if(priority(move1, move2, (*pokemon1).speed, (*pokemon2).speed)) {
        printf("Pokemon 2 går först :)\n");
    } else {
        printf("Pokemon 1 går först :)\n");
    }
}
