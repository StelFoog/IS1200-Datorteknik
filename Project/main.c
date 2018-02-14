#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "battle.h"


unsigned short statCalc(int base, char level, char hp) {
    char iv = rand() % 16;
    short stat = floor((double) (2 * base + iv + 22) * level / 100);
    if(hp) {
        stat += level + 10;
    } else {
        stat += 5;
    }

    return stat;
}

int statTotal(pokemonStruct pkmn) {
    return pkmn.baseHp+pkmn.baseSpeed+pkmn.basePyAtk+pkmn.basePyDef+pkmn.baseSpAtk+pkmn.baseSpDef;
}

void importPokemon(battlePokemon *pokemon, pokemonStruct pkmn) {
    strcpy((*pokemon).name, pkmn.name);
    (*pokemon).pokemonType1 = pkmn.pokemonType1;
    (*pokemon).pokemonType2 = pkmn.pokemonType2;
    for(int i = 0; i < MOVEAMOUNT; i++) {
        (*pokemon).moveset[i] = pkmn.moveset[i];
    }
    (*pokemon).level = (rand() % 10) + 45;
    (*pokemon).hp = statCalc(pkmn.baseHp, (*pokemon).level, 1);
    (*pokemon).speed = statCalc(pkmn.baseSpeed, (*pokemon).level, 0);
    (*pokemon).pyAtk = statCalc(pkmn.basePyAtk, (*pokemon).level, 0);
    (*pokemon).pyDef = statCalc(pkmn.basePyDef, (*pokemon).level, 0);
    (*pokemon).spAtk = statCalc(pkmn.baseSpAtk, (*pokemon).level, 0);
    (*pokemon).spDef = statCalc(pkmn.baseSpDef, (*pokemon).level, 0);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    const moveStruct mysticFire = {"Mystic Fire", fire, 65, 100, 0x10};
    const moveStruct slam = {"Slam", normal, 80, 75, 0x00};
    const moveStruct quickAttack = {"Quick Attack", 40, 100, 0x01};
    const moveStruct wingAttack = {"Wing Attack", 60, 100, 0x00};
    const moveStruct airCutter = {"Air Cutter", 60, 95, 0x10};
    const moveStruct leafBlade = {"Leaf Blade", 85, 95, 0x00};
    const moveStruct mudBomb = {"Mud Bomb", 75, 85, 0x10};

    const pokemonStruct charizord = {"Charizord", fire, flying, {mysticFire, slam, wingAttack}, 78, 100, 84, 78, 109, 85};
    const pokemonStruct grassGround = {"grassGround", grass, ground, {leafBlade, quickAttack, mudBomb}, 87, 110, 95, 90, 63, 82};
    //const pokemonStruct icePoke = {"icePoke", ice, null, {}}

    /*
    printf("Damage calc: %d\n",
            damageCalc(5, charman.moveset[0].power, 25, 5,
            stab(charman.moveset[0].attackType, charman.pokemonType1, charman.pokemonType2),
            typeEffect(charman.moveset[0].attackType, electric), typeEffect(charman.moveset[0].attackType, null)));
    *//*
    printf("Size of short: %lu\n", sizeof(short));
    printf("Stat Total Charizord: %d\n", statTotal(charizord));
    printf("Stat Total Gg: %d\n", statTotal(grassGround));
    */
    battlePokemon pokemon1, pokemon2;

    importPokemon(&pokemon1, charizord);
    importPokemon(&pokemon2, grassGround);
    battlePhase(&pokemon1, &pokemon2, pokemon1.moveset[0], pokemon2.moveset[2]);

    return 0;
}
