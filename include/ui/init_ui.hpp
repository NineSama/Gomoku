#ifndef INIT_UI_HPP
#define INIT_UI_HPP

#include <X11/Xlib.h>
#include <iostream>
#include "board/board.hpp"

#define GRID_SIZE 19
#define WINDOW_SIZE 760
#define CELL_SIZE (WINDOW_SIZE / GRID_SIZE)

struct UIData {
    Display* display;
    Window window;
    GC gc;
    int screen;
};

XColor getColor(Display* display, const std::string& colorName);
UIData initUI();
bool clickCoordinates(int x, int y, int& gridX, int& gridY);
void drawBoard(const UIData& ui, const Board& board);
void drawStone(const UIData& ui, int x, int y, XColor color);
void drawGrid(const UIData& ui);

#endif
