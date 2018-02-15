#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "battle.h"

unsigned int damageCalc(int level, unsigned char basePow, short atk, short def, unsigned char stab, unsigned short typeMod) {
    double result = (((((level * 2 / 5 + 2) * basePow * (atk / def) / 50) + 2) * stab * typeMod) / 1000);
    return ((unsigned int) ceil(result));
}
    // returns typechart value * 10
unsigned char typeEffect(type move, type opponent) {
    double result;
    switch(move) {
        // fire as atack typechart
        case fire:
            switch(opponent) {
                case fire:
                    result = 5;
                    break;
                case water:
                    result = 5;
                    break;
                case grass:
                    result = 20;
                    break;
                case ground:
                    result = 5;
                    break;
                case ice:
                    result = 20;
                    break;
                default:
                    result = 10;
            }
            break;
        // water as attack typechart
        case water:
            switch(opponent) {
                case fire:
                    result = 5;
                    break;
                case water:
                    result = 5;
                case grass:
                    result = 20;
                    break;
                case ground:
                    result = 20;
                    break;
                case ice:
                    result = 5;
                    break;
                default:
                    result = 10;
            }
            break;
        // grass as attack typechart
        case grass:
            switch(opponent) {
                case fire:
                    result = 5;
                    break;
                case water:
                    result = 20;
                    break;
                case grass:
                    result = 5;
                    break;
                case ground:
                    result = 20;
                    break;
                case ice:
                    result = 5;
                    break;
                case flying:
                    result = 5;
                    break;
                default:
                    result = 10;
            }
            break;
        // ground as attack typechart
        case ground:
            switch(opponent) {
                case fire:
                    result = 20;
                    break;
                case grass:
                    result = 5;
                    break;
                case flying:
                    result = 0;
                    break;
                case electric:
                    result = 20;
                    break;
                default:
                    result = 10;
            }
            break;
        // flying as attack typechart
        case flying:
            switch(opponent) {
                case grass:
                    result = 20;
                    break;
                case ice:
                    result = 5;
                    break;
                case electric:
                    result = 5;
                    break;
                default:
                    result = 10;
            }
            break;
        // ice as attack typechart
        case ice:
            switch(opponent) {
                case fire:
                    result = 5;
                    break;
                case water:
                    result = 5;
                    break;
                case grass:
                    result = 20;
                    break;
                case ground:
                    result = 20;
                    break;
                default:
                    result = 10;
            }
            break;
        // electric as atack typechart
        case electric:
            switch(opponent) {
                case water:
                    result = 20;
                    break;
                case grass:
                    result = 5;
                    break;
                case ground:
                    result = 0;
                    break;
                case flying:
                    result = 20;
                    break;
                case electric:
                    result = 5;
                    break;
                default:
                    result = 10;
            }
            break;
        default:
            result = 10;
    }
    return result;
}
    // returns type modification * 100
unsigned short typeMod(moveStruct move, battlePokemon pkmn) {
    return (typeEffect(move.attackType, pkmn.pokemonType1) * typeEffect(move.attackType, pkmn.pokemonType2));
}
    // checks for Same-Type Attack Bonus
unsigned char stab(moveStruct move, battlePokemon pkmn) {
    double result = 10;
    if(move.attackType == pkmn.pokemonType1 || move.attackType == pkmn.pokemonType2) {
        result = 15;
    }
    return result;
}
    // returns which pokemon goes first
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
    // executes an attack
void attackExec(moveStruct move, battlePokemon atkPokemon, battlePokemon *defPokemon) {
    short atk;
    short def;
    if(move.phySpecPrio & 0xf0) { // test if move is physical or special
        atk = atkPokemon.spAtk;
        def = (*defPokemon).spDef;
    } else {
        atk = atkPokemon.pyAtk;
        def = (*defPokemon).pyDef;
    }
    if(move.accuracy > (rand() % 100)) { // attack hit
        printf("%d\n", damageCalc(atkPokemon.level, move.power, atk, def, stab(move, atkPokemon), typeMod(move, (*defPokemon))));
        (*defPokemon).hp -= damageCalc(atkPokemon.level, move.power, atk, def, stab(move, atkPokemon), typeMod(move, (*defPokemon)));
        if((*defPokemon).hp > 60000) { // sets HP to 0 if overflow has occured
            (*defPokemon).hp = 0;
        }
    } else { // attack missed
        printf("The attack missed! o.o\n");
    }
}
    // one turn of battle
void battlePhase(battlePokemon *pokemon1, battlePokemon *pokemon2, moveStruct move1, moveStruct move2) {
    if(priority(move1, move2, (*pokemon1).speed, (*pokemon2).speed)) { // checks priority
        printf("pokemon 2 goes first\n");
        attackExec(move2, (*pokemon2), pokemon1);
        if((*pokemon1).hp > 0) { // checks for faint
            attackExec(move1, (*pokemon1), pokemon2);
        }
    } else {
        printf("pokemon 1 goes first\n");
        attackExec(move1, (*pokemon1), pokemon2); //
        if((*pokemon2).hp > 0) { // checks for faint
            attackExec(move2, (*pokemon2), pokemon1);
        }
    }
}
