#include <stdio.h>
#include "dots.h"
#include "graphics.h" // Remove this after abstracting cleanup to a different function

void processInput(progVars* pv) {
   SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            TTF_Quit();
            SDL_Quit();
            free(layerCount);
            exit(0);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                TTF_Quit();
                SDL_Quit();
                free(layerCount);
                exit(0);
            }
            break;
        case SDL_MOUSEMOTION:
            pv->mouseLoc.x = event.motion.x;
            pv->mouseLoc.y = event.motion.y;
            if (pv->mouseDown) {
                pv->curLine.p2 = getNearestDot(pv->mouseLoc);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                // Set first point for line
                pv->curLine.p1 = getNearestDot(pv->mouseLoc);
                pv->curLine.p2 = pv->curLine.p1;
                pv->mouseDown = 1;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                pv->mouseDown = 0;
                pv->curLine = {{0, 0}, {0, 0}};
                pv->oldLine = pv->curLine;
            }
            break;
        }
    }
}
