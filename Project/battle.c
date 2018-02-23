#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "battle.h"
#include "flags.h"
#include "io.h"
#include "animation.h"

    // returns damage dealt with the given variables
unsigned int damageCalc(unsigned char level, unsigned char basePow, unsigned short atk, unsigned short def, unsigned char stab, unsigned short typeMod) {
    //double result = ((((((level * 2 / 5) + 2) * basePow * (atk / def) / 50) + 2) * stab * typeMod) / 1000);
    double result = (level * 2/5)+2;
    result = result *basePow * atk/def;
    result = (result / 50) + 2;
    result = (result * stab * typeMod) / 1000;

    if(typeMod > 100) {
        //printf("It's super effective!\n");
    } else if(typeMod == 0) {
        //printf("It doesn't affect the opposing pokemon!\n");
    } else if(typeMod < 100) {
        //printf("It's not very effective...\n");
    }
    //printf("Dealt %d damage\n", ((unsigned int) ceil(result)));
    //return ((unsigned int) ceil(result));
    result++;
    return (unsigned int) result;
}

    // returns typechart value * 10
unsigned char typeEffect(type * move, type * opponent) {
    double result;
    switch(*move) {
        // fire as atack typechart
        case fire:
            switch(*opponent) {
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
            switch(*opponent) {
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
            switch(*opponent) {
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
            switch(*opponent) {
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
            switch(*opponent) {
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
            switch(*opponent) {
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
            switch(*opponent) {
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
unsigned short typeMod(moveStruct * move, battlePokemon * pkmn) {
    return (typeEffect(&move->attackType, &pkmn->pokemonType1) * typeEffect(&move->attackType, &pkmn->pokemonType2));
}

    // checks for Same-Type Attack Bonus
unsigned char stab(moveStruct * move, battlePokemon * pkmn) {
    double result = 10;
    if(move->attackType == pkmn->pokemonType1 || move->attackType == pkmn->pokemonType2) {
        result = 15;
    }
    return result;
}

    // returns which pokemon goes first
unsigned char priority(moveStruct * move1, moveStruct * move2, battlePokemon * pokemon1, battlePokemon * pokemon2) {
    unsigned char retval = 0;
    unsigned short speed1 = pokemon1->speed * getStageBuff(pokemon1->speedStage);
    unsigned short speed2 = pokemon2->speed * getStageBuff(pokemon2->speedStage);
    if((move1->phySpecPrio & 0x0f) < (move2->phySpecPrio & 0x0f)) {
        retval = 1;
    } else if((move1->phySpecPrio & 0x0f) == (move2->phySpecPrio & 0x0f)) {
        if(speed1 < speed2) {
            retval = 1;
        }
    }
    return retval;
}

    // returns stagebuff
double getStageBuff(signed char stage) {
    double returnValue;
        // checks if it should fetch atack or defence stat (should be 0 for speed)
    if(stage > 0) {
        returnValue = (double) (stage + 2) / 2;
    } else {
        returnValue = (double) 2 / (2 + (stage * -1));
    }
    ////printf("%f\n", returnValue);
    return returnValue;
}

    // sets stagebuff with given increase/decrease
void setStageBuff(signed char *stage, signed char increaseDecrease) {
    (*stage) += increaseDecrease;
    if((*stage) < (-6)) {
        (*stage) = -6;
    } else if((*stage) > 6) {
        (*stage) = 6;
    }
}

    // executes an attack
void attackExec(moveStruct * move, battlePokemon * atkPokemon, battlePokemon * defPokemon) {
    if((((*move).phySpecPrio >> 4) & 0x3 ) != 2) {
        unsigned short atk;
        unsigned short def;
        // test if move is physical or special
        if((*move).phySpecPrio & 0xf0) {   // if special
            atk = (*atkPokemon).spAtk * getStageBuff((*atkPokemon).spAtkStage);
            def = (*defPokemon).spDef * getStageBuff((*defPokemon).spDefStage);
        } else {                        // if physical
            atk = (*atkPokemon).pyAtk * getStageBuff((*atkPokemon).pyAtkStage);
            //printf("atk stage: %f\n", getStageBuff((*atkPokemon).pyAtkStage));
            def = (*defPokemon).pyDef * getStageBuff((*defPokemon).pyDefStage);
            //printf("def stage: %f\n", getStageBuff((*defPokemon).pyDefStage));
        }
        if((*move).accuracy > (randImplemented() % 100)) { // attack hit
            ////printf("%d\n", damageCalc((*atkPokemon).level, move.power, atk, def, stab(move, (*atkPokemon)), typeMod(move, (*defPokemon))));
            (*defPokemon).hp -= damageCalc((*atkPokemon).level, move->power, atk, def, stab(move, atkPokemon), typeMod(move, defPokemon));
            if((*defPokemon).hp > 60000) { // sets HP to 0 if overflow has occured
                (*defPokemon).hp = 0;
            }
        } else { // attack missed
            //printf("The attack missed! o.o\n");
        }
    }
    
    switch((*move).moveEffectID) {
        case 1:
            //printf("Used protect.\n");
            if(((*move).phySpecPrio >> 6) > 0) {
                //printf("But it failed!\n");
            } else {
                (*move).phySpecPrio = (*move).phySpecPrio | (2 << 6);
                setFlag(protectID, atkPokemon);
            }
            break;
        case 2:
            //printf("Used curse.\n");
            setStageBuff(&(*atkPokemon).speedStage, -1);
            setStageBuff(&(*atkPokemon).pyAtkStage, +1);
            setStageBuff(&(*atkPokemon).pyDefStage, +1);
            break;
        case 3:
            setStageBuff(&(*defPokemon).pyAtkStage, -2);
            break;
        case 4:
            setStageBuff(&(*defPokemon).pyAtkStage, -1);
            break;
        default:
            //printf("Moveset error\n");
            break;

}

    // lowers the flag count of all moves on a pokemon
void moveFlagReset(battlePokemon *pkmn) {
    int i;
    for(i = 0; i < MOVEAMOUNT; i++) {
        if(((*pkmn).moveset[i].phySpecPrio >> 6)) {
            (*pkmn).moveset[i].phySpecPrio = ((*pkmn).moveset[i].phySpecPrio & 0x3f) | ((((*pkmn).moveset[i].phySpecPrio >> 6) - 1) << 6);
        }
    }
}

    // one turn of battle
void battlePhase(battlePokemon *pokemon1, battlePokemon *pokemon2, moveStruct *move1, moveStruct *move2) {
    if(priority(move1, move2, pokemon1, pokemon2)) { // checks priority
        attackAnimation(move2, pokemon1, pokemon2, 2);
        attackExec(move2, pokemon2, pokemon1);
        //printf("\n");
        if((*pokemon1).hp > 0) { // checks for faint
            idleAnimationDelay(pokemon1, pokemon2, 10);
            //printf("pokemon 1 used %s\n", (*move1).name);
            if(getFlag(protectID, *pokemon2)) {
                //printf("Didn't break through protect\n");
            } else {
                attackAnimation(move1, pokemon1, pokemon2, 1);
                attackExec(move1, pokemon1, pokemon2);
            }
            //printf("\n");
        }
    } else {
        //printf("pokemon 1 used %s\n", (*move1).name);
        attackAnimation(move1, pokemon1, pokemon2, 1);
        attackExec(move1, pokemon1, pokemon2);
        //printf("\n");
        if((*pokemon2).hp > 0) { // checks for faint
            idleAnimationDelay(pokemon1, pokemon2, 10);
            //printf("pokemon 2 used %s\n", (*move2).name);
            if(getFlag(protectID, *pokemon1)) {
                //printf("Didn't break through protect\n");
            } else {
                attackAnimation(move2, pokemon1, pokemon2, 2);
                attackExec(move2, pokemon2, pokemon1);
            }
            //printf("\n");
        }
    }
    clrAllFlags(pokemon1);
    clrAllFlags(pokemon2);
    moveFlagReset(pokemon1);
    moveFlagReset(pokemon2);
}
