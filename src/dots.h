#pragma once

/*
 * This file takes care of everythign specifically pertaining to the dots.
 * Dots are spaced apart isometrically
 */

#include <vector>

#define DOT_DISTANCE 30
#define DOT_DIST_W DOT_DISTANCE
#define DOT_DIST_H (DOT_DISTANCE * 1.73205 / 2)

typedef struct {
    int x;
    int y;
} point;

bool operator ==(point a, point b);
bool operator !=(point a, point b);

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
    line toErase; // line that tells draw which line to erase when pressing undo
    std::vector<line> lines; // Vector of all lines that have been drawn
} progVars; // The variables used by an instance of this program

point getNearestDot(point p);
bool isDot(point p);
