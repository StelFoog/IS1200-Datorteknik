#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "battle.h"

int statCalc(int base, char level, char iv, char hp) {
    int stat = floor((double) (2 * base + iv + 22) * level / 100);
    if(hp) {
        stat += level + 10;
    } else {
        stat += 5;
    }

    return stat;
}

int statTotal(pokemonStruct pkmn) {

    return pkmn.baseHp+pkmn.baseSpeed+pkmn.baseAtk+pkmn.baseDef+pkmn.baseSAtk+pkmn.baseSDef;
}

int main(int argc, char const *argv[]) {
    const moveStruct mystciFire = {"Mystic Fire", fire, 65, 100, 0x10};
    const moveStruct slam = {"Slam", normal, 80, 75, 0x00};
    const moveStruct quickAttack = {"Quick Attack", 40, 100, 0x01};
    const moveStruct wingAttack = {"Wing Attack", 60, 100, 0x00};
    const moveStruct airCutter = {"Air Cutter", 60, 95, 0x10};
    const moveStruct leafBlade = {"Leaf Blade", 85, 95, 0x00};
    const moveStruct mudBomb = {"Mud Bomb", 75, 85, 0x10};

    const pokemonStruct charizord = {"Charizord", fire, flying, {mystciFire, slam, wingAttack}, 78, 100, 84, 78, 109, 85};
    const pokemonStruct grassGround = {"grassGround", grass, ground, {leafBlade, quickAttack, mudBomb}, 87, 110, 95, 90, 63, 82};

    /*
    printf("Damage calc: %d\n",
            damageCalc(5, charman.moveset[0].power, 25, 5,
            stab(charman.moveset[0].attackType, charman.pokemonType1, charman.pokemonType2),
            typeEffect(charman.moveset[0].attackType, electric), typeEffect(charman.moveset[0].attackType, null)));
    */
    printf("Stat Total Charizord: %d\n", statTotal(charizord));
    printf("Stat Total Gg: %d\n", statTotal(grassGround));
    return 0;
}
