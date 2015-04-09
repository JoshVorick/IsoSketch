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
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                TTF_Quit();
                SDL_Quit();
                free(layerCount);
                exit(0);
                break;
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                pv->ctrlDown = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                pv->ctrlDown = 0;
                break;
            case SDLK_z:
                if (pv->lines.size() > 0) {
                    pv->toErase = pv->lines.back();
                    pv->lines.pop_back();
                }
                break;
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
                // Update the drawn line one last time
                // Otherwise there's a chance line has changed since it was drawn
                drawLine(pv->oldLine.p1.x, pv->oldLine.p1.y, pv->oldLine.p2.x, pv->oldLine.p2.y, 0x000000);
                drawLine(pv->curLine.p1.x, pv->curLine.p1.y, pv->curLine.p2.x, pv->curLine.p2.y, 0xffffff);
                pv->lines.push_back(pv->curLine);
                pv->curLine = {{0, 0}, {0, 0}};
                pv->oldLine = pv->curLine;
            }
            break;
        }
    }
}
