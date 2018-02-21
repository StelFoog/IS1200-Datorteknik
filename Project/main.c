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
int statTotal(pokemonStruct * pkmn) {
    return pkmn->baseHp+pkmn->baseSpeed+pkmn->basePyAtk+pkmn->basePyDef+pkmn->baseSpAtk+pkmn->baseSpDef;
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

unsigned char moveSelect(battlePokemon * pokemon) {
    unsigned char timeoutcount = 0, cursorBlink = 0, buttonCheck = 1;;
    signed char selected = 0;
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
        drawMoves(pokemon->moveset[0].name, (0 + 0), (8 + 0));
        drawMoves(pokemon->moveset[1].name, (0 + 64), (8 + 0));
        drawMoves(pokemon->moveset[2].name, (0 + 0), (0 + 40));

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
    unsigned char timeoutcount = 0;
    while(timeoutcount < n) {
        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
            timeoutcount++;           // Increment timeoutcount
            IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
    }
}

char * hpString(char str[], unsigned short hp, unsigned char curleng) {
    unsigned char thousand = 0, hundred = 0, ten = 0, one = 0;
    while(1) {
        if(hp < 1000) {
            break;
        } else {
            thousand++;
            hp -= 1000;
        }
    }
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
    thousand += 48;
    hundred += 48;
    ten += 48;
    one += 48;
    str[curleng + 0] = thousand;
    str[curleng + 1] = hundred;
    str[curleng + 2] = ten;
    str[curleng + 3] = one;
    str[curleng + 4] = 0;
    return str;
}

char * statString(char str[], unsigned char stat) {
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
    return str;
}

static const char * strings[] = {"       ",
    "Normal ",  "Fire   ",  "Water  ",  "Grass  ",
    "Ground ",  "Flying ",  "Ice    ",  "Eletric",
};

const pokemonStruct * choosePokemon(const pokemonStruct * list[], unsigned char n){
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
        if(selected > n-1){
            selected = 0;
        }
        if(selected < 0){
            selected = n-1;
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
<<<<<<< HEAD
        drawString(str, 104, 34);
=======
        drawString(str, 108, 34);
>>>>>>> c7ce1c63ed9ba183d4b4b2021e50066f9cd984b5

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
<<<<<<< HEAD
        drawString(str, 104, 50);
=======
        drawString(str, 108, 50);
>>>>>>> c7ce1c63ed9ba183d4b4b2021e50066f9cd984b5

        drawSprite(4 * selected, 56, pkmnSelectCursor, 4, 8);
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
    const pokemonStruct temit = {"TEMIT", grass, ground, {leafBlade, quickAttack, mudBomb}, 87, 110, 95, 90, 63, 82, &temitSprite};
    const pokemonStruct qminx = {"QMINX", grass, null, {leafBlade, curse, protect}, 116, 55, 65, 104, 43, 138, &qminxSprite};
    //const pokemonStruct icePoke = {"icePoke", ice, null, {}}

    init();
    unsigned char timeoutcount = 0;
    while(!(getBtns() & 4)){
        randImplemented();
    }
    while(getBtns() & 4);

    battlePokemon pokemon1, pokemon2;
    const pokemonStruct * pokemonList[2] = {&temit, &qminx};
    clrScr();
    drawString("Player 1", 3, 2);
    drawString("Select Pokemon", 8, 12);
    update();
    delay(10);
    const pokemonStruct * player1 = choosePokemon(pokemonList, 2);
    while(getBtns());
    clrScr();
    drawString("Player 2", 3, 2);
    drawString("Select Pokemon", 8, 12);
    update();
    delay(10);
    const pokemonStruct * player2 = choosePokemon(pokemonList, 2);
    while (getBtns());
    importPokemon(&pokemon1, *player1);
    importPokemon(&pokemon2, *player2);
    char p1hp[] = "player 1 HP:        ";
    char p2hp[] = "player 2 HP:        ";
    unsigned char moveIndex1, moveIndex2;
    while(1) {
        clrScr();
        while(getBtns());
        delay(3);
        moveIndex1 = moveSelect(&pokemon1);
        while(getBtns());
        delay(3);
        moveIndex2 = moveSelect(&pokemon2);
        battlePhase(&pokemon1, &pokemon2, &pokemon1.moveset[moveIndex1], &pokemon2.moveset[moveIndex2]);
        timeoutcount = 0;
        while (timeoutcount < 10)  {
            clrScr();
            drawSprite(96, 0, pokemon2.sprite->front, 32, 32);
            drawSprite(0, 32, pokemon1.sprite->back, 32, 32);
            update();
            if(IFS(0) & 0x100){         // check if interrupt flag is enabled
              timeoutcount++;           // Increment timeoutcount
              IFSCLR(0) = 0x100;        //Reset the timeout flag
            }
        }
        clrScr();
        hpString(p1hp, pokemon1.hp, 14);
        hpString(p2hp, pokemon2.hp, 14);
        drawString(p1hp, 8, 20);
        drawString(p2hp, 8, 40);
        update();
        while(!(getBtns() & 4));
        if(pokemon1.hp == 0) {
            clrScr();
            drawString("Player 2 won!", 8, 20);
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
