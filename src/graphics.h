#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#define WIDTH 1920
#define HEIGHT 1080

#define FPS 16
#define TIME_BETWEEN_FRAMES (1000 / FPS)

#define CUBE_ROOT_3 1.73205

#define DOT_DISTANCE 20
#define DOT_DIST_W DOT_DISTANCE
#define DOT_DIST_H (DOT_DISTANCE * CUBE_ROOT_3 / 2)

extern SDL_Surface *screen;
extern char* layerCount;

bool isDot(int x, int y);
void setPixel(int x, int y, Uint32 color);
void drawLine(int x1, int y1, int x2, int y2, Uint32 color); // Bresenham's algorithm from Rosetta code
SDL_Surface* loadImage(char* name);
void drawString(char* text, int x, int y, TTF_Font* font, int centerX, int centerY, Uint32 fgColor, Uint32 bgColor);
void drawImage(SDL_Surface* image, int x, int y);
