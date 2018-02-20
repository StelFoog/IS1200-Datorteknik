#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "battle.h"
#include "flags.h"

    // calculates the final stat value for one stat
unsigned short statCalc(int base, char level, char hp) {
    char iv = rand() % 16; // random IV between 0 and 15
    short stat = floor((double) (2 * base + iv + 22) * level / 100);
    if(hp) {
        stat += level + 10;
    } else {
        stat += 5;
    }

    return stat;
}
    // debugging – the total value of a pokemons base stats
int statTotal(pokemonStruct pkmn) {
    return pkmn.baseHp+pkmn.baseSpeed+pkmn.basePyAtk+pkmn.basePyDef+pkmn.baseSpAtk+pkmn.baseSpDef;
}
    // transfers pokemonStruct to battlePokemon
void importPokemon(battlePokemon *pokemon, pokemonStruct pkmn) {
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
    (*pokemon).speedStage = 0;
    (*pokemon).pyAtkStage = 0;
    (*pokemon).pyDefStage = 0;
    (*pokemon).spAtkStage = 0;
    (*pokemon).spDefStage = 0;
}
    // prints all the final stats
void printStats(battlePokemon pokemon) {
    printf("Level: %4d\n", pokemon.level);
    printf("HP:    %4d\n", pokemon.hp);
    printf("Speed: %4d\n", pokemon.speed);
    printf("PyAtk: %4d\n", pokemon.pyAtk);
    printf("PyDef: %4d\n", pokemon.pyDef);
    printf("SpAtk: %4d\n", pokemon.spAtk);
    printf("SpDef: %4d\n", pokemon.spDef);
    printf("Speed Stage: %4hhi\n", pokemon.speedStage);
    printf("PyAtk Stage: %4hhi\n", pokemon.pyAtkStage);
    printf("PyDef Stage: %4hhi\n", pokemon.pyDefStage);
    printf("SpAtk Stage: %4hhi\n", pokemon.spAtkStage);
    printf("SpDef Stage: %4hhi\n", pokemon.spDefStage);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    // all moves
    const moveStruct protect =      {1, normal, 0, 100, 0x25, "protect"};
    const moveStruct mysticFire =   {0, fire, 65, 100, 0x10, "mysticFire"};
    const moveStruct slam =         {0, normal, 80, 75, 0x00, "slam"};
    const moveStruct quickAttack =  {0, normal, 40, 100, 0x01, "quickAttack"};
    const moveStruct wingAttack =   {0, flying, 60, 100, 0x00, "wingAttack"};
    const moveStruct airCutter =    {0, flying, 60, 95, 0x10, "airCutter"};
    const moveStruct leafBlade =    {0, grass, 85, 95, 0x00, "leafBlade"};
    const moveStruct mudBomb =      {0, ground, 75, 85, 0x10, "mudBomb"};
    const moveStruct curse =        {2, null, 0, 100, 0x20, "curse"};

    // all pokemon
    const pokemonStruct charizord = {fire, flying, {mysticFire, slam, wingAttack}, 78, 100, 84, 78, 109, 85};
    const pokemonStruct grassGround = {grass, ground, {leafBlade, quickAttack, mudBomb}, 87, 110, 95, 90, 63, 82};
    const pokemonStruct qminx = {grass, null, {leafBlade, curse, protect}, 116, 55, 65, 104, 43, 138};
    //const pokemonStruct icePoke = {"icePoke", ice, null, {}}
    /*
    printf("Stat Total Charizord: %d\n", statTotal(charizord));
    printf("Stat Total Gg: %d\n", statTotal(grassGround));
    printf("Stat Total Qminx: %d\n", statTotal(qminx));
    */
    battlePokemon pokemon1, pokemon2;
    importPokemon(&pokemon1, charizord);
    importPokemon(&pokemon2, qminx);

    printf("pkmn1:\n");
    printStats(pokemon1);
    printf("pkmn2:\n");
    printStats(pokemon2);
    printf("\n");
    for(int i = 0; i < 3; i++) {
        battlePhase(&pokemon1, &pokemon2, &pokemon1.moveset[2], &pokemon2.moveset[1]);
        printf("pkmn1:\n");
        printStats(pokemon1);
        printf("pkmn2:\n");
        printStats(pokemon2);
        printf("\n");
        if(pokemon1.hp <= 0) {
            break;
        } else if(pokemon2.hp <= 0) {
            break;
        }
    }
    battlePhase(&pokemon1, &pokemon2, &pokemon1.moveset[2], &pokemon2.moveset[0]);
    battlePhase(&pokemon1, &pokemon2, &pokemon1.moveset[2], &pokemon2.moveset[0]);
    /*
    printf("%lu\n", sizeof(moveStruct));
    printf("%lu\n", sizeof(battlePokemon));
    */
    return 0;
}
