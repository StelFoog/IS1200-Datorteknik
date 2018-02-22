#include "main.h"
#include "io.h"
#include "animation.h"
#include "driver/graphics.h"
#include "driver/OLED_I2C.h"

void idleAnimation(battlePokemon *pkmn1, battlePokemon *pkmn2) {
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

            drawString("P1 HP: ", 52, 128-62);
            hpString(str, pkmn1->hp, 0);
            drawSprite(str, 52, 20);

            drawString("P2 HP: ", 2, 2);
            hpString(str, pkmn2->hp, 0);
            drawSprite(str, 2, 44);

            update();
            moveCount++;
        }
    }
}

void attackAnimation(moveStruct *atk, battlePokemon *pkmn1, battlePokemon *pkmn2, char atkingPkmn) {
    if(((atk->phySpecPrio >> 4) & 3) == 2) {
        drawSprite(96, 0, pkmn2->sprite->front, 32, 32);
        drawSprite(0, 32, pkmn1->sprite->back, 32, 32);

        drawString("P1 HP: ", 52, 128-62);
        hpString(str, pkmn1->hp, 0);
        drawSprite(str, 52, 20);

        drawString("P2 HP: ", 2, 2);
        hpString(str, pkmn2->hp, 0);
        drawSprite(str, 2, 44);
    }
}
