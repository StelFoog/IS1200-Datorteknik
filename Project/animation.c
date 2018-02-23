#include "main.h"
#include "io.h"
#include <pic32mx.h>
#include "animation.h"
#include "driver/graphics.h"
#include "driver/OLED_I2C.h"

void idleAnimationBtn(battlePokemon *pkmn1, battlePokemon *pkmn2) {
    unsigned char moveCount = 0, timeoutcount = 0;
    char str[4];
    while(!(getBtns() & 4)) {
        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
          timeoutcount++;           // Increment timeoutcount
          IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
        if(timeoutcount > 1) {
            clrScr();
            timeoutcount = 0;
            if(moveCount > 1)
                moveCount = 0;
            drawSprite(96, moveCount, pkmn2->sprite->front, 32, 32);
            drawSprite(0, 32-moveCount, pkmn1->sprite->back, 32, 32);

            drawString("P1 HP: ",  128-62, 52);
            hpString(str, pkmn1->hp, 0);
            drawString(str, 110, 52);

            drawString("P2 HP: ", 2, 2);
            hpString(str, pkmn2->hp, 0);
            drawString(str, 44, 2);

            update();
            moveCount++;
        }
    }
}

void idleAnimationDelay(battlePokemon *pkmn1, battlePokemon *pkmn2, unsigned char delay) {
    unsigned char moveCount = 0, timeoutcount = 0, counter = 0;
    char str[4];
    while(counter < delay) {
        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
          timeoutcount++;           // Increment timeoutcount
          counter++;
          IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
        if(timeoutcount > 1) {
            clrScr();
            timeoutcount = 0;
            if(moveCount > 1)
                moveCount = 0;
            drawSprite(96, moveCount, pkmn2->sprite->front, 32, 32);
            drawSprite(0, 32-moveCount, pkmn1->sprite->back, 32, 32);

            drawString("P1 HP: ",  128-62, 52);
            hpString(str, pkmn1->hp, 0);
            drawString(str, 110, 52);

            drawString("P2 HP: ", 2, 2);
            hpString(str, pkmn2->hp, 0);
            drawString(str, 44, 2);

            update();
            moveCount++;
        }
    }
}

void attackAnimation(moveStruct *atk, battlePokemon *pkmn1, battlePokemon *pkmn2, char atkingPkmn) {
    unsigned char timeoutcount = 0, moveCount = 0;
    char str[4];
    if(((atk->phySpecPrio >> 4) & 3) == 2) {
        while(timeoutcount < 10) {
            clrScr();
            if(IFS(0) & 0x100){         // check if interrupt flag is enabled
                timeoutcount++;           // Increment timeoutcount
                if(moveCount>4) {
                    moveCount = 4;
                } else {
                    moveCount++;
                }
                IFSCLR(0) = 0x100;        //Reset the timeout flag
            }
            drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
            drawSprite(0, 32, pkmn1->sprite->back, 32, 32);

            drawString("P1 HP: ",  128-62, 52);
            hpString(str, pkmn1->hp, 0);
            drawString(str, 110, 52);

            drawString("P2 HP: ", 2, 2);
            hpString(str, pkmn2->hp, 0);
            drawString(str, 44, 2);

            if(atkingPkmn == 1) {
                drawSprite(8, 44-moveCount, statusMove,16,16);
            } else {
                drawSprite(104, 12-moveCount, statusMove,16,16);
            }
            update();
        }
    } else if(((atk->phySpecPrio >> 4) & 3) == 1) {
        while(timeoutcount < 12) {
            clrScr();
            if(IFS(0) & 0x100){         // check if interrupt flag is enabled
                timeoutcount++;           // Increment timeoutcount
                IFSCLR(0) = 0x100;        //Reset the timeout flag
            }
            if(atkingPkmn == 1) {
                if(!((timeoutcount == 9) || (timeoutcount == 11))) {
                    drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
                }
                if(timeoutcount < 9) {
                    drawSprite(24 + (7 * timeoutcount), 32 - (2 * timeoutcount), spAtkSprite, 8, 8);
                }
                drawSprite(0, 32, pkmn1->sprite->back, 32, 32);
            } else {
                drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
                if(timeoutcount < 9) {
                    drawSprite(96 - (7 * timeoutcount), 16 + (2 * timeoutcount), spAtkSprite, 8, 8);
                }
                if(!((timeoutcount == 9) || (timeoutcount == 11))) {
                    drawSprite(0, 32, pkmn1->sprite->back, 32, 32);
                }
            }

            drawString("P1 HP: ",  128-62, 52);
            hpString(str, pkmn1->hp, 0);
            drawString(str, 110, 52);

            drawString("P2 HP: ", 2, 2);
            hpString(str, pkmn2->hp, 0);
            drawString(str, 44, 2);

            update();
        }
    } else {
        while(timeoutcount < 10) {
            clrScr();
            if(IFS(0) & 0x100){         // check if interrupt flag is enabled
                timeoutcount++;           // Increment timeoutcount
                IFSCLR(0) = 0x100;        //Reset the timeout flag
            }
            if(atkingPkmn == 1) {
                if(timeoutcount < 9) {
                    drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
                    drawSprite(7 * timeoutcount, 32 - (2 * timeoutcount), pkmn1->sprite->back, 32, 32);
                } else {
                    if(timeoutcount == 10) {
                        drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
                    }
                    drawSprite(63, 14, pkmn1->sprite->back, 32, 32);
                }
            } else {
                if(timeoutcount < 9) {
                    drawSprite(96 - (7 * timeoutcount), 2 * timeoutcount, pkmn2->sprite->front, 32, 32);
                    drawSprite(0, 32, pkmn1->sprite->back, 32, 32);
                } else {
                    drawSprite(96 - (7 * 9), 18, pkmn2->sprite->front, 32, 32);
                    if(timeoutcount == 10) {
                        drawSprite(0, 32, pkmn1->sprite->back, 32, 32);
                    }
                }
            }

            drawString("P1 HP: ",  128-62, 52);
            hpString(str, pkmn1->hp, 0);
            drawString(str, 110, 52);

            drawString("P2 HP: ", 2, 2);
            hpString(str, pkmn2->hp, 0);
            drawString(str, 44, 2);

            update();
        }
    }
}

void faintAnimation(battlePokemon *pkmn1, battlePokemon *pkmn2, char faintedPkmn) {
    unsigned char moveCount = 0, timeoutcount = 0, counter = 0;
    char str[4];
    while(counter < 15) {
        if(IFS(0) & 0x100){         // check if interrupt flag is enabled
          timeoutcount++;           // Increment timeoutcount
          counter++;
          IFSCLR(0) = 0x100;        //Reset the timeout flag
        }
        if(timeoutcount > 1) {
            timeoutcount = 0;
            if(moveCount > 1)
                moveCount = 0;
            moveCount++;
        }
        clrScr();

        if(faintedPkmn == 2) {
            if(counter < 4) {
                drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
            } else if(counter < 12) {
                drawSprite(96, counter-4, pkmn2->sprite->front, 32, 32);
            }
            drawSprite(0, 32-moveCount, pkmn1->sprite->back, 32, 32);
        } else {
            if(counter < 4) {
                drawSprite(0, 32, pkmn1->sprite->back, 32, 32);
            } else if(counter < 12) {
                drawSprite(96, 32 + counter-4, pkmn2->sprite->front, 32, 32);
            }
            drawSprite(96, moveCount, pkmn2->sprite->front, 32, 32);
        }

        drawString("P1 HP: ",  128-62, 52);
        hpString(str, pkmn1->hp, 0);
        drawString(str, 110, 52);

        drawString("P2 HP: ", 2, 2);
        hpString(str, pkmn2->hp, 0);
        drawString(str, 44, 2);

        update();
    }
}
