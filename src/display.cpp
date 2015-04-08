#include "dots.h"
#include "graphics.h"

void drawAllDots() {
    // Not the most efficient way of doing all the initial dots, but it works
    point tp = {0, 0};
    for (tp.x = 0; tp.x < WIDTH; tp.x += DOT_DIST_W / 2) {
        for (tp.y = 0; tp.y < HEIGHT; tp.y += DOT_DIST_H / 2) {
            point temp = getNearestDot(tp);
            setPixel(temp.x, temp.y, 0xffffff);
        }
    }
}

void drawScreen(progVars *pv) {
    // Highlight nearest point
    point nearestDot = getNearestDot(pv->mouseLoc);

    if (nearestDot.x < WIDTH && nearestDot.y < HEIGHT) {
        // Draw over oldPixel
        setPixel(pv->oldPoint.x, pv->oldPoint.y, 0xffffff);
        setPixel(pv->oldPoint.x+1, pv->oldPoint.y, 0x000000);
        setPixel(pv->oldPoint.x+1, pv->oldPoint.y+1, 0x000000);
        setPixel(pv->oldPoint.x, pv->oldPoint.y+1, 0x000000);
        // Update pv->oldPoint to the new one
        pv->oldPoint.x = nearestDot.x;
        pv->oldPoint.y = nearestDot.y;
        // Draw the new point
        setPixel(nearestDot.x, nearestDot.y, 0x44ff44);
        setPixel(nearestDot.x+1, nearestDot.y, 0x44ff44);
        setPixel(nearestDot.x+1, nearestDot.y+1, 0x44ff44);
        setPixel(nearestDot.x, nearestDot.y+1, 0x44ff44);
    }

    if (pv->mouseDown) {
        // Erase pv->oldLine
        drawLine(pv->oldLine.p1.x, pv->oldLine.p1.y, pv->oldLine.p2.x, pv->oldLine.p2.y, 0x000000);
        // Draw pv->curLine
        drawLine(pv->curLine.p1.x, pv->curLine.p1.y, pv->curLine.p2.x, pv->curLine.p2.y, 0xffffff);
        pv->oldLine = pv->curLine;
    }

    SDL_Flip(screen);
}
