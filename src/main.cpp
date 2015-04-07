#include <stdio.h>
#include "graphics.h"

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point start;
    point end;
} line;

point getNearestDot(point p);

int main(void){
    bool notDone = 1;
    
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

    bool mouseDown = 0;

    // Initialize some points;
    point oldPoint = {0, 0}; // Represents the last point that was hovered over
    point mouseLoc = {0, 0};

    line curLine = {{0, 0}, {0, 0}};
    line oldLine = curLine;

    // draw all the white points
    Uint32 white = 0xffffff;

    // Not the most efficient way of doing all the initial dots, but it works
    point tp = {0, 0};
    for (tp.x = 0; tp.x < WIDTH; tp.x += DOT_DIST_W / 2) {
        for (tp.y = 0; tp.y < HEIGHT; tp.y += DOT_DIST_H / 2) {
            point temp = getNearestDot(tp);
            setPixel(temp.x, temp.y, white);
        }
    }

    SDL_Flip(screen);

    while(notDone) {
        // get input
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
                mouseLoc.x = event.motion.x;
                mouseLoc.y = event.motion.y;
                if (mouseDown) {
                    curLine.end = getNearestDot(mouseLoc);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Set first point for line
                    curLine.start = getNearestDot(mouseLoc);
                    curLine.end = curLine.start;
                    mouseDown = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = 0;
                    curLine = {{0, 0}, {0, 0}};
                    oldLine = curLine;
                }
                break;
            }
        }

        // Highlight nearest point
        point nearestDot = getNearestDot(mouseLoc);

        if (nearestDot.x <WIDTH && nearestDot.y < HEIGHT) {
            // Draw over oldPixel
            setPixel(oldPoint.x, oldPoint.y, 0xffffff);
            setPixel(oldPoint.x+1, oldPoint.y, 0x000000);
            setPixel(oldPoint.x+1, oldPoint.y+1, 0x000000);
            setPixel(oldPoint.x, oldPoint.y+1, 0x000000);
            // Update oldPoint to the new one
            oldPoint.x = nearestDot.x;
            oldPoint.y = nearestDot.y;
            // Draw the new point
            setPixel(nearestDot.x, nearestDot.y, 0x44ff44);
            setPixel(nearestDot.x+1, nearestDot.y, 0x44ff44);
            setPixel(nearestDot.x+1, nearestDot.y+1, 0x44ff44);
            setPixel(nearestDot.x, nearestDot.y+1, 0x44ff44);
        }

        if (mouseDown) {
            // Erase oldLine
            drawLine(oldLine.start.x, oldLine.start.y, oldLine.end.x, oldLine.end.y, 0x000000);
            // Draw curLine
            drawLine(curLine.start.x, curLine.start.y, curLine.end.x, curLine.end.y, 0xffffff);
            oldLine = curLine;
        }
        SDL_Flip(screen);
    }

    TTF_Quit();
    SDL_Quit();

    free(layerCount);

    exit(0);
}

// Returns coordinates of dot nearest to input coordinates
point getNearestDot(point p) {
        //p.x += DOT_DIST_W / 2; // This will make later int casts
        //p.y = p.y + 1; // round to nearest instead of floor
        int y = (p.y + DOT_DIST_H / 2) / DOT_DIST_H;
        int offset = (y % 2 == 0) ? DOT_DIST_W / 2 : 0;
        double x = (p.x + offset) / DOT_DIST_W + (y % 2) / 2.0;
        return {x * DOT_DIST_W, y * DOT_DIST_H};
}
