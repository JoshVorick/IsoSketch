#include "dots.h"

bool operator ==(point a, point b) {
    return (a.x == b.x) && (a.y == b.y);
}

// Returns coordinates of dot nearest to input coordinates
point getNearestDot(point p) {
    //p.x += DOT_DIST_W / 2; // This will make later int casts
    //p.y = p.y + 1; // round to nearest instead of floor
    int y = (p.y + DOT_DIST_H / 2) / DOT_DIST_H;
    int offset = (y % 2 == 0) ? DOT_DIST_W / 2 : 0;
    double x = (p.x + offset) / DOT_DIST_W + (y % 2) / 2.0;
    return {(int)(x * DOT_DIST_W), (int)(y * DOT_DIST_H)};
}

bool isDot(point p) {
    return (p == getNearestDot(p));
}
