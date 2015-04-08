#include "init.h"
#include "graphics.h"

void initialize(progVars* pv) {
   
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_ANYFORMAT);

    if (screen == NULL) {
        printf("Failed to initialize screen\n");
    }

    SDL_WM_SetCaption("IsoSketch", NULL);

    layerCount = (char*)malloc(sizeof(char) * WIDTH * HEIGHT);

    if (layerCount == NULL) {
        printf("Failed to initialize layerCount\n");
    }

    for (int i=0; i < WIDTH*HEIGHT; i++) {
        layerCount[i] = 0;
    }

    pv->mouseDown = 0;

    // Set all elements to zero
    pv->oldPoint = {0, 0}; // Represents the last point that was hovered over
    pv->mouseLoc = {0, 0};
    pv->curLine = {{0, 0}, {0, 0}};
    pv->oldLine = pv->curLine;
    pv->toErase = pv->curLine;
}

void cleanup() {
    TTF_Quit();
    SDL_Quit();

    free(layerCount);

    exit(0);
}
