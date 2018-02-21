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
unsigned short statCalc(int base, char level, char hp) {
    //char iv = 8;
    char iv = randImplemented() % 16; // random IV between 0 and 15
    //short stat = floor((double) (2 * base + iv + 22) * level / 100);
    short stat = (2 * base + iv + 22) * level / 100;
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
    int i;
    (*pokemon).pokemonType1 = pkmn.pokemonType1;
    (*pokemon).pokemonType2 = pkmn.pokemonType2;
    for(i = 0; i < MOVEAMOUNT; i++) {
        (*pokemon).moveset[i] = pkmn.moveset[i];
    }
    //(*pokemon).level = (rand() % 10) + 45;
    (*pokemon).level = 50;
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
    (*pokemon).sprite = pkmn.sprite;
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

unsigned char moveSelect(battlePokemon pokemon) {
    unsigned char timeoutcount = 0;
    signed char selected = 0, cursorBlink = 0, buttonCheck = 1;
    while(1) {
        update();
        if(getBtns() && buttonCheck) {
            buttonCheck = 0;
            if(getBtns() == (1 << 0)) {
                selected++;
            }
            if(getBtns() == (1 << 1)) {
                selected--;
            }
            if(getBtns() == (1 << 2)) {
                return selected;
            }
        }

        if(selected > 3) {
            selected = 0;
        } else if(selected < 0) {
            selected = 3;
        }

        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
          timeoutcount++;           // Increment timeoutcount
          IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
        if(timeoutcount == 5){      // If timeoutcount is 5
          buttonCheck = 1;
          cursorBlink++;
          timeoutcount = 0;
        }

        clrScr();
        drawMoves(pokemon.moveset[0].name, (0 + 0), (8 + 0));
        drawMoves(pokemon.moveset[1].name, (0 + 64), (8 + 0));
        drawMoves(pokemon.moveset[2].name, (0 + 0), (0 + 40));

        if(cursorBlink % 2) {
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
    unsigned char timeoutcount;
    while(timeoutcount < n) {
        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
            timeoutcount++;           // Increment timeoutcount
            IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
    }
}

int main(void) {
    //srand(time(NULL));
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
    // all pokemon
    //const pokemonStruct charizord = {fire, flying, {mysticFire, slam, wingAttack}, 78, 100, 84, 78, 109, 85};
    const pokemonStruct grassGround = {grass, ground, {leafBlade, quickAttack, mudBomb}, 87, 110, 95, 90, 63, 82, &temitSprite};
    const pokemonStruct qminx = {grass, null, {leafBlade, curse, protect}, 116, 55, 165, 104, 43, 138, &qminxSprite};
    //const pokemonStruct icePoke = {"icePoke", ice, null, {}}

    init();
    unsigned char timeoutcount = 0;
    while(!(getBtns() & 4)){
        randImplemented();
    }
    char temp1[4];
    char longTemp1[20];
    char temp2[4];
    char longTemp2[20];

    battlePokemon pokemon1, pokemon2;
    importPokemon(&pokemon1, grassGround);
    importPokemon(&pokemon2, qminx);

    unsigned char moveIndex1, moveIndex2;
    while(1) {
        clrScr();
        while(getBtns());
        delay(3);
        moveIndex1 = moveSelect(pokemon1);
        while(getBtns());
        delay(3);
        moveIndex2 = moveSelect(pokemon2);
        battlePhase(&pokemon1, &pokemon2, &pokemon1.moveset[moveIndex1], &pokemon2.moveset[moveIndex2]);
        timeoutcount = 0;
        while (timeoutcount < 10)  {
            clrScr();
            drawSprite(96, 0, (*(pokemon2.sprite)).front, 32, 32);
            drawSprite(0, 32, (*(pokemon1.sprite)).back, 32, 32);
            update();
            if(IFS(0) & 0x100){         // check if interrupt flag is enabled
              timeoutcount++;           // Increment timeoutcount
              IFSCLR(0) = 0x100;        //Reset the timeout flag
            }
        }
        sprintf(&temp1, "%hu", pokemon1.hp);
        strcat(&longTemp1, "Player 1 HP: ");
        strcat(&longTemp1, temp1);
        sprintf(&temp2, "%hu", pokemon2.hp);
        strcat(&longTemp2, "Player 2 HP: ");
        strcat(&longTemp2, temp2);
        clrScr();
        drawString(longTemp1, 8, 16);
        drawString(longTemp2, 8, 40);
        update();
        delay(10);
        if(pokemon1.hp == 0) {
            clrScr();
            DrawString("Player 2 won!", 8, 20);
            update();
            break;
        } else if(pokemon2.hp == 0) {
            clrScr();
            drawString("Player 1 won!", 8, 20);
            update();
            break;
        }
    }
    //clrScr();
    //drawSprite(0,0,startScreen,128, 64);
    //setPixel(64, 32);
    //update();
    return 0;
}
