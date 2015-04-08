#include <stdio.h>
#include "display.h"
#include "dots.h"
#include "init.h"
#include "input.h"
#include "graphics.h"

int main(void) {
    bool notDone = 1;
    int fpsLimit = TIME_BETWEEN_FRAMES;

    progVars myVars;

    initialize(&myVars);

    drawAllDots();
    SDL_Flip(screen);

    while(notDone) {

        processInput(&myVars);

        drawScreen(&myVars);

        unsigned int ticks = SDL_GetTicks();
        if (ticks < fpsLimit)
            SDL_Delay(fpsLimit - ticks);
        fpsLimit = SDL_GetTicks() + TIME_BETWEEN_FRAMES;
    }

    TTF_Quit();
    SDL_Quit();

    free(layerCount);

    exit(0);
}
