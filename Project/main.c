#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>
//#include <time.h>
#include <pic32mx.h>
#include "main.h"
#include "battle.h"
#include "flags.h"
#include "io.h"
#include "driver/graphics.h"
#include "driver/OLED_I2C.h"



    // pseudo-random number generator
unsigned int randImplemented (void) {
   static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27;
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}
    // calculates the final stat value for one stat
unsigned short statCalc(char base, char level, char hp) {
    char iv = randImplemented() % 16; // random IV between 0 and 15
    short stat = (2 * base + iv + 22) * level / 100;
    if(hp) {
        stat += level + 10;
    } else {
        stat += 5;
    }

    return stat;
}
    // debugging – the total value of a pokemons base stats
int statTotal(const pokemonStruct *pkmn) {
    return pkmn->baseHp + pkmn->baseSpeed + pkmn->basePyAtk + pkmn->basePyDef + pkmn->baseSpAtk + pkmn->baseSpDef;
}
    // transfers pokemonStruct to battlePokemon
void importPokemon(battlePokemon *pokemon, const pokemonStruct * pkmn) {
    int i;
    (*pokemon).pokemonType1 = pkmn->pokemonType1;
    (*pokemon).pokemonType2 = pkmn->pokemonType2;
    for(i = 0; i < MOVEAMOUNT; i++) {
        (*pokemon).moveset[i] = pkmn->moveset[i];
    }
    //(*pokemon).level = (rand() % 10) + 45;
    (*pokemon).level = 50;
    (*pokemon).hp = statCalc(pkmn->baseHp, (*pokemon).level, 1);
    (*pokemon).speed = statCalc(pkmn->baseSpeed, (*pokemon).level, 0);
    (*pokemon).pyAtk = statCalc(pkmn->basePyAtk, (*pokemon).level, 0);
    (*pokemon).pyDef = statCalc(pkmn->basePyDef, (*pokemon).level, 0);
    (*pokemon).spAtk = statCalc(pkmn->baseSpAtk, (*pokemon).level, 0);
    (*pokemon).spDef = statCalc(pkmn->baseSpDef, (*pokemon).level, 0);
    (*pokemon).speedStage = 0;
    (*pokemon).pyAtkStage = 0;
    (*pokemon).pyDefStage = 0;
    (*pokemon).spAtkStage = 0;
    (*pokemon).spDefStage = 0;
    (*pokemon).sprite = pkmn->sprite;
}
    // prints all the final stats
void printStats(battlePokemon pokemon) {
    //printf("Level: %4d\n", pokemon.level);
    //printf("HP:    %4d\n", pokemon.hp);
    //printf("Speed: %4d\n", pokemon.speed);
    //printf("PyAtk: %4d\n", pokemon.pyAtk);
    //printf("PyDef: %4d\n", pokemon.pyDef);
    //printf("SpAtk: %4d\n", pokemon.spAtk);
    //printf("SpDef: %4d\n", pokemon.spDef);
    //printf("Speed Stage: %4hhi\n", pokemon.speedStage);
    //printf("PyAtk Stage: %4hhi\n", pokemon.pyAtkStage);
    //printf("PyDef Stage: %4hhi\n", pokemon.pyDefStage);
    //printf("SpAtk Stage: %4hhi\n", pokemon.spAtkStage);
    //printf("SpDef Stage: %4hhi\n", pokemon.spDefStage);
}

unsigned char moveSelect(battlePokemon * pokemon) {
    unsigned char timeoutcount = 0, cursorBlink = 0, buttonCheck = 1;;
    signed char selected = 0;
    while(1) {
        update();
        if(getBtns() && buttonCheck) {
            buttonCheck = 0;
            cursorBlink = 1;
            timeoutcount = 0;
            if(getBtns() == (1 << 0)) {
                selected++;
            }
            if(getBtns() == (1 << 1)) {
                selected--;
            }
            if(getBtns() == (1 << 2)) {
                while(getBtns());
                return selected;
            }
        }

        if(selected >= MOVEAMOUNT) {
            selected = 0;
        } else if(selected < 0) {
            selected = MOVEAMOUNT - 1;
        }

        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
          timeoutcount++;           // Increment timeoutcount
          IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
        if(timeoutcount == 5){      // If timeoutcount is 5
          buttonCheck = 1;
          if(cursorBlink){
              cursorBlink = 0;
          } else {
              cursorBlink = 1;
          }
          timeoutcount = 0;
        }

        clrScr();
        drawMoves(pokemon->moveset[0].name, 0, 8);
        drawMoves(pokemon->moveset[1].name, 64, 8);
        drawMoves(pokemon->moveset[2].name, 0, 40);
        drawMoves(pokemon->moveset[3].name, 64, 40);

        if(cursorBlink) {
            switch (selected) {
                case 0:
                    drawSprite(64-16, 8 + 0, cursor, 8, 8);
                    break;
                case 1:
                    drawSprite(128-16, 8 + 0, cursor, 8, 8);
                    break;
                case 2:
                    drawSprite(64-16, 8 + 32, cursor, 8, 8);
                    break;
                case 3:
                    drawSprite(128-16, 8 + 32, cursor, 8, 8);
                    break;
                default:
                    break;
            }
        }
    }
}

void delay(unsigned char n) {
    unsigned char timeoutcount = 0;
    while(timeoutcount < n) {
        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
            timeoutcount++;           // Increment timeoutcount
            IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
    }
}

char *hpString(char str[], unsigned short hp, unsigned char curleng) {
    unsigned char hundred = 0, ten = 0, one = 0;
    while(1) {
        if(hp < 100) {
            break;
        } else {
            hundred++;
            hp -= 100;
        }
    }
    while(1) {
        if(hp < 10) {
            break;
        } else {
            ten++;
            hp -= 10;
        }
    }
    while(1) {
        if(hp < 1) {
            break;
        } else {
            one++;
            hp -= 1;
        }
    }
    hundred += 48;
    ten += 48;
    one += 48;
    str[curleng + 0] = hundred;
    str[curleng + 1] = ten;
    str[curleng + 2] = one;
    str[curleng + 3] = 0;
    return str;
}

char *statString(char str[], unsigned char stat) {
    unsigned char hundred = 0, ten = 0, one = 0;
    while(1) {
        if(stat < 100) {
            break;
        } else {
            hundred++;
            stat -= 100;
        }
    }
    while(1) {
        if(stat < 10) {
            break;
        } else {
            ten++;
            stat -= 10;
        }
    }
    while(1) {
        if(stat < 1) {
            break;
        } else {
            one++;
            stat -= 1;
        }
    }
    hundred += 48;
    ten += 48;
    one += 48;
    str[0] = hundred;
    str[1] = ten;
    str[2] = one;
    str[3] = 0;
    return str;
}

static const char *strings[] = {"       ",
    "Normal ",  "Fire   ",  "Water  ",  "Grass  ",
    "Ground ",  "Flying ",  "Ice    ",  "Eletric",
};

const pokemonStruct *choosePokemon(const pokemonStruct * list[]){
    char str[4];
    signed char selected = 0;
    while(1) {
        update();
        if(getBtns()) {
            if(getBtns() == (1 << 0)) {
                selected++;
                while(getBtns() & 1);
            }
            if(getBtns() == (1 << 1)) {
                selected--;
                while(getBtns() & 2);
            }
            if(getBtns() == (1 << 2)) {
                while(getBtns() & 4);
                return list[selected];
            }
        }
        if(selected > POKEMON_COUNT-1){
            selected = 0;
        }
        if(selected < 0){
            selected = POKEMON_COUNT-1;
        }
        clrScr();
        drawSprite(96,0, list[selected]->sprite->front, 32, 32);
        drawString(list[selected]->name, 0, 2);
        drawString(strings[list[selected]->pokemonType1],0,10);
        drawString(strings[list[selected]->pokemonType2],52,10);
        drawString("Stats", 0, 24);

        drawString("HP:    ", 2, 34);
        statString(str, list[selected]->baseHp);
        drawString(str, 44, 34);

        drawString("Speed: ", 68, 34);
        statString(str, list[selected]->baseSpeed);
        drawString(str, 108, 34);

        drawString("PyAtk: ", 2, 42);
        statString(str, list[selected]->basePyAtk);
        drawString(str, 44, 42);

        drawString("SpAtk: ", 68, 42);
        statString(str, list[selected]->baseSpAtk);
        drawString(str, 108, 42);

        drawString("PyDef: ", 2, 50);
        statString(str, list[selected]->basePyDef);
        drawString(str, 44, 50);

        drawString("SpDef: ", 68, 50);
        statString(str, list[selected]->baseSpDef);
        drawString(str, 108, 50);

        drawSprite(4 * selected, 60, pkmnSelectCursor, 4, 4);
    }
}

int main(void) {
    // all moves
    const moveStruct protect =      {1, normal, 0, 100, 0x25, "Protect"};
    const moveStruct mysticFire =   {0, fire, 65, 100, 0x10, "Mystic Fire"};
    const moveStruct slam =         {0, normal, 80, 75, 0x00, "Slam"};
    const moveStruct quickAttack =  {0, normal, 40, 100, 0x01, "Quick Attack"};
    const moveStruct wingAttack =   {0, flying, 60, 100, 0x00, "Wing Attack"};
    const moveStruct airCutter =    {0, flying, 60, 95, 0x10, "Air Cutter"};
    const moveStruct leafBlade =    {0, grass, 85, 95, 0x00, "Leaf Blade"};
    const moveStruct mudBomb =      {0, ground, 75, 85, 0x10, "Mud Bomb"};
    const moveStruct curse =        {2, null, 0, 100, 0x20, "Curse"};
    const moveStruct charm =        {3, normal, 0, 100, 0x20, "Charm"};
    const moveStruct strength =     {0, normal, 75, 90, 0x00, "Strength"};
    const moveStruct shockWave =    {0, electric, 70, 100, 0x10, "Shock Wave"};
    const moveStruct bulldoze =     {4, ground, 60, 95, 0x00, "Bulldoze"};
    // all pokemon

    const pokemonStruct temit = {"TEMIT", grass, ground, {leafBlade, quickAttack, mudBomb, charm}, 87, 110, 95, 80, 63, 92, &temitSprite};
    const pokemonStruct qminx = {"QMINX", grass, null, {leafBlade, curse, protect, strength}, 116, 55, 65, 104, 43, 138, &qminxSprite};
    const pokemonStruct bidaul = {"BIDAUL", flying, null, {airCutter, slam, protect, shockWave}, 73, 147, 55, 54, 133, 68, &nullSprite};
    const pokemonStruct seahorse = {"SEAHORSE", water, null, {slam, quickAttack, strength, protect}, 73, 147, 55, 53, 133, 68, &seahorseSprite}; //EDIT STATS
    const pokemonStruct ventios = {"VENTIOS", flying,null , {airCutter, quickAttack, strength, protect}, 73, 147, 55, 53, 133, 68, &ventiosSprite}; //EDIT STATS
    const pokemonStruct bloomint = {"BLOOMINT", fire, null, {mysticFire, slam, charm, quickAttack}, 78, 100, 84, 78, 109, 85, &bloomintSprite}; //EDIT STATS


    //const pokemonStruct icePoke = {"icePoke", ice, null, {}}

    init();
    unsigned char timeoutcount = 0;
    while(!(getBtns() & 4)){
        randImplemented();
    }
    battlePokemon pokemon1, pokemon2;
    const pokemonStruct * pokemonList[POKEMON_COUNT] = {&bloomint, &temit, &qminx, &bidaul, &seahorse,&ventios};
    clrScr();
    while(1){
        while(getBtns() & 4);
        drawString("Player 1", 3, 2);
        drawString("Select Pokemon", 8, 12);
        update();
        delay(10);
        const pokemonStruct * player1 = choosePokemon(pokemonList);
        clrScr();
        drawString("Player 2", 3, 2);
        drawString("Select Pokemon", 8, 12);
        update();
        delay(10);
        const pokemonStruct * player2 = choosePokemon(pokemonList);
        importPokemon(&pokemon1, player1);
        importPokemon(&pokemon2, player2);
        char p1hp[] = "player 1 HP:        ";
        char p2hp[] = "player 2 HP:        ";
        unsigned char moveIndex1, moveIndex2;
        while(1) {
            while(getBtns());
            clrScr();
            drawString("Player 1", 3, 2);
            drawString("Choose move",8,12);
            update();
            delay(10);
            moveIndex1 = moveSelect(&pokemon1);
            clrScr();
            drawString("Player 2", 3, 2);
            drawString("Choose move",8,12);
            update();
            delay(10);
            moveIndex2 = moveSelect(&pokemon2);
            idleAnimationDelay(&pokemon1, &pokemon2, 10);
            battlePhase(&pokemon1, &pokemon2, &pokemon1.moveset[moveIndex1], &pokemon2.moveset[moveIndex2]);

            if(pokemon1.hp == 0) {
                faintAnimation(&pokemon1, &pokemon2, 1);
                clrScr();
                drawString("Player 2 won!", 8, 20);
                update();
                delay(20);
                clrScr();
                break;
            } else if(pokemon2.hp == 0) {
                faintAnimation(&pokemon1, &pokemon2, 2);
                clrScr();
                drawString("Player 1 won!", 8, 20);
                update();
                delay(20);
                clrScr();
                break;
            }
            idleAnimationDelay(&pokemon1, &pokemon2, 8);
        }
    }
    /*
    printf("%d\n", statTotal(&ferretas));
    printf("%d\n", statTotal(&temit));
    printf("%d\n", statTotal(&qminx));
    printf("%d\n", statTotal(&bidaul));
    */
    return 0;
}
