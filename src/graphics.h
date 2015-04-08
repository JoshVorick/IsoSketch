#pragma once

/*
 * This takes care of all low level graphics
 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#define WIDTH 400
#define HEIGHT 400

#define FPS 16
#define TIME_BETWEEN_FRAMES (1000 / FPS)

extern SDL_Surface *screen;
extern char* layerCount;

void setPixel(int x, int y, Uint32 color);
void drawLine(int x1, int y1, int x2, int y2, Uint32 color); // Bresenham's algorithm from Rosetta code
SDL_Surface* loadImage(char* name);
void drawString(char* text, int x, int y, TTF_Font* font, int centerX, int centerY, Uint32 fgColor, Uint32 bgColor);
void drawImage(SDL_Surface* image, int x, int y);
