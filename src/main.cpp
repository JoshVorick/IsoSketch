#include <stdio.h>
#include "display.h"
#include "dots.h"
#include "input.h"
#include "graphics.h"

int main(void) {
    bool notDone = 1;
    int fpsLimit = TIME_BETWEEN_FRAMES;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_ANYFORMAT);

    if (screen == NULL) {
        printf("Failed to initialize screen\n");
    }

    layerCount = (char*)malloc(sizeof(char) * WIDTH * HEIGHT);

    if (layerCount == NULL) {
        printf("Failed to initialize layerCount\n");
    }

    for (int i=0; i < WIDTH*HEIGHT; i++) {
        layerCount[i] = 0;
    }

    progVars myVars;

    myVars.mouseDown = 0;

    // Initialize some points;
    myVars.oldPoint = {0, 0}; // Represents the last point that was hovered over
    myVars.mouseLoc = {0, 0};

    myVars.curLine = {{0, 0}, {0, 0}};
    myVars.oldLine = myVars.curLine;

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
