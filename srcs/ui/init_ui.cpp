#include "ui/init_ui.hpp"

XColor getColor(Display* display, const std::string& colorName) {
    XColor color;
    Colormap colormap = DefaultColormap(display, 0);
    if (!XParseColor(display, colormap, colorName.c_str(), &color) ||
        !XAllocColor(display, colormap, &color)) {
        std::cerr << "Failed to allocate color: " << colorName << std::endl;
        color.pixel = 0;
    }
    return color;
}

UIData initUI()
{
    UIData ui = {NULL, 0, 0, 0};
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "Cannot open X display\n";
        return ui;
    }

    XColor grey = getColor(display, "#656565");
    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        0, 0, // x, y
        WINDOW_SIZE, WINDOW_SIZE,
        0, WhitePixel(display, screen), grey.pixel
    );
    XSelectInput(display, window, ExposureMask | ButtonPressMask | StructureNotifyMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, NULL);
    XSetForeground(display, gc, BlackPixel(display, screen));
    XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinMiter);

    ui.display = display;
    ui.window = window;
    ui.gc = gc;
    ui.screen = screen;
    return ui;
}

bool clickCoordinates(int x, int y, int& gridX, int& gridY)
{
    if (x < 0 || x >= WINDOW_SIZE || y < 0 || y >= WINDOW_SIZE)
        return false;
    gridX = x / CELL_SIZE;
    gridY = y / CELL_SIZE;
    return true;
}

void drawBoard(const UIData& ui, const Board& board)
{
    XClearWindow(ui.display, ui.window);
    drawGrid(ui);
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (board.getCell(x, y) == BLACK)
                drawStone(ui, x, y, getColor(ui.display, "#000000"));
            else if (board.getCell(x, y) == WHITE)
                drawStone(ui, x, y, getColor(ui.display, "#FFFFFF"));
        }
    }
}

void drawStone(const UIData& ui, int x, int y, XColor color)
{
    int margin = CELL_SIZE;
    int cx = margin + x * CELL_SIZE;
    int cy = margin + y * CELL_SIZE;
    int radius = CELL_SIZE / 2 - 2;

    XSetForeground(ui.display, ui.gc, color.pixel);
    XFillArc(ui.display, ui.window, ui.gc,
             cx - radius, cy - radius,
             2 * radius, 2 * radius,
             0, 360*64);
    XSetForeground(ui.display, ui.gc, BlackPixel(ui.display, ui.screen));
    XFlush(ui.display);
}

void drawGrid(const UIData& ui)
{
    for (int i = 0; i <= GRID_SIZE; ++i) {
        int pos = i * CELL_SIZE;
        XDrawLine(ui.display, ui.window, ui.gc, pos, 0, pos, WINDOW_SIZE);
        XDrawLine(ui.display, ui.window, ui.gc, 0, pos, WINDOW_SIZE, pos);
    }
    XFlush(ui.display);
}