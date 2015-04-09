#include "graphics.h"
#include "dots.h"

SDL_Surface *screen;
char* layerCount;

void setPixel(int x, int y, Uint32 color) {
    if (x >= WIDTH || y >= HEIGHT) {
        return;
    }
    if (isDot({x, y})) {
        color = 0xffffff;
    }
    // Update layerCount
    if (color == 0) {
        // If setting to black (erasing)
        if (layerCount[y*WIDTH + x] > 0) {
            layerCount[y*WIDTH + x]--;
        }
    } else {
        layerCount[y*WIDTH + x]++;
    }

    // Draw if we need to
    if (layerCount[y*WIDTH + x] == 0 || color != 0) {
        Uint8 *pixel = (Uint8*)screen->pixels;
        pixel += (y * screen->pitch) + (x * sizeof(Uint32));
        *((Uint32*)pixel) = color;
    }
}

void drawLine(int x1, int y1, int x2, int y2, Uint32 color) {
    // Bresenham's algorithm from rosetta code
    const bool steep = (abs(y2 -y1) > abs(x2 - x1));
    if (steep) {
        // swap(x1, y1)
        int temp = x1;
        x1 = y1;
        y1 = temp;
        // swap(x2, y2);
        temp = x2;
        x2 = y2;
        y2 = temp;
    }

    if (x1 > x2) {
        // swap(x1, x2)
        int temp = x1;
        x1 = x2;
        x2 = temp;
        // swap(y1, y2);
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    const int dx = x2 - x1;
    const int dy = abs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    const int maxX = x2;

    for (int x=x1; x < maxX; x++) {
        if (steep) {
            setPixel(y, x, color);
        } else {
            setPixel(x, y, color);
        }

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawLine(line l, Uint32 color) {
    drawLine(l.p1.x, l.p1.y, l.p2.x, l.p2.y, color);
}

SDL_Surface *loadImage(char *name) {
    printf("load image start\n");
    //load image all fancy-shmancy-like
    printf("load image end\n");
    return IMG_Load(name); //SDL_DisplayFormat(IMG_Load(name));    
};

void drawString(char *text, int x, int y, TTF_Font *font, int centerX, int centerY, SDL_Color foregroundColor, SDL_Color backgroundColor){
    //printf("draw string start\n");
    SDL_Rect dest;
    SDL_Surface *surface = TTF_RenderUTF8_Shaded(font, text, foregroundColor, backgroundColor);
    if(surface == NULL)
        printf("KABOOOOOOM!!!\n");

    dest.x = (centerX == 1 ? (screen->w - surface->w) / 2 : x);
    dest.y = (centerY == 1 ? (screen->h - surface->h) / 2 : y);
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_BlitSurface(surface, NULL, screen, &dest);

    SDL_FreeSurface(surface);
    //printf("draw string end\n");
};

void drawImage(SDL_Surface *image, int x, int y){
    //printf("draw image start\n");
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    SDL_BlitSurface(image, NULL, screen, &dest);
    //printf("draw image end\n");
};
