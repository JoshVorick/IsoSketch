#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include "display.h"
#include "graphics.h"
#include "saves.h"

using namespace std;

std::string path("./myDrawing.isosketch");

void save(progVars* pv) {
    // TODO: prompt for file name

    // save all lines to file name
    ofstream outFILE(path, ios::out | ofstream::binary);
    outFILE.write(reinterpret_cast<const char *>(&(pv->lines[0])), pv->lines.size()*sizeof(line));

    /*
    std::ofstream FILE(path, std::ios::out | std::ofstream::binary);
    std::copy(pv->lines.begin(), pv->lines.end(), std::ostreambuf_iterator<char>(FILE));
    */
}

void load(progVars* pv) {
    // TODO: prompt for file name


    pv->lines.clear();

    // load all lines from file
    ifstream inFILE(path, ios::in | ifstream::binary);

    if (!inFILE) {
        cout << "Cannot open file to load from" << endl;
        return;
    }
    line l;
    while (inFILE.read(reinterpret_cast<char *>(&l), sizeof(l)))
        pv->lines.push_back(l);
    /*
    std::ifstream INFILE(path, std::ios::in | std::ifstream::binary);
    std::istreambuf_iterator<char> iter(INFILE);
    std::copy(iter.begin(), iter.end(), std::back_inserter(pv->lines));
    */

    // draw the new file
    SDL_FillRect(screen, NULL, 0x000000);
    drawAllDots();
    for (auto &l : pv->lines) {
        drawLine(l.p1.x, l.p1.y, l.p2.x, l.p2.y, 0xffffff);
    }
    SDL_Flip(screen);
}
