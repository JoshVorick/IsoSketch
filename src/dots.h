#pragma once

/*
 * This file takes care of everythign specifically pertaining to the dots.
 * Dots are spaced apart isometrically
 */

#define DOT_DISTANCE 30
#define DOT_DIST_W DOT_DISTANCE
#define DOT_DIST_H (DOT_DISTANCE * 1.73205 / 2)

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point p1;
    point p2;
} line;

typedef struct {
    bool mouseDown;
    bool ctrlDown;
    point mouseLoc;
    point oldPoint;
    line curLine;
    line oldLine;
} progVars; // The variables used by an instance of this program

point getNearestDot(point p);
bool isDot(point p);
