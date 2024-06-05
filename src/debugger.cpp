#include "debugger.hpp"

#include <ncurses.h>

#include <iostream>

#include "logger.hpp"

#undef getch

Debugger::Debugger() {
    // Create main window
    WINDOW *p_mainWin = getLargeWindow();
    this->p_mainWin = p_mainWin;

    checkColorDisponibility(p_mainWin);
    initColors();
    initHeader();
    initWindows(p_mainWin, RAM_BROWSER_WIDTH, SYSTEM_STATUS_HEIGHT,
                LOG_TOP_OFFSET);
};

Debugger::~Debugger() {
    this->displayLogMessage("E | The debugger is being destroyed. Press a key to continue...");
    flushinp();
    getch();
    endwin();
    std::cout << "Debugger destroyed :D" << std::endl;
};

WINDOW *Debugger::getLargeWindow() {
    WINDOW *p_largeWindow = initscr();
    cbreak();
    refresh();

    auto totalHeight = MIN_LOG_HEIGHT + SYSTEM_STATUS_HEIGHT;
    auto totalWidth = MIN_LOG_WIDTH + RAM_BROWSER_WIDTH;

    while (getmaxx(p_largeWindow) < totalWidth ||
           getmaxy(p_largeWindow) < totalHeight) {
        endwin();
        std::cout << "Please resize window and press y to continue"
                  << std::endl;
        while (getchar() != 'y') {
        };
        refresh();
    }

    // Prevent chars from appearing in the debugger
    noecho();
    return p_largeWindow;
}

void Debugger::checkColorDisponibility(WINDOW *p_winToCheck) {
    if (!has_colors()) {
        endwin();
        throw "No color display";
    }
};

void Debugger::initColors() {
    start_color();
    init_pair(HEADER_PAIR, COLOR_WHITE, COLOR_RED);
    init_pair(WARN_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(ERR_PAIR, COLOR_WHITE, COLOR_RED);
    init_pair(DEFAULT_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(INFO_PAIR, COLOR_CYAN, COLOR_BLACK);
};

void Debugger::initHeader() {
    mvprintw(0, 0, "GuiNESs debugger - 2024");
    mvprintw(1, 0,
             "[F1] Halt/resume execution     [F2] Next frame     [F3] Next "
             "instruction     [F4] Clear log     [ESC] Quit");
    bkgd(COLOR_PAIR(HEADER_PAIR));
    refresh();
};

void Debugger::initWindows(WINDOW *p_mainWin, int ram_width, int sysinfo_height,
                           int log_top_offset) {
    int logWidth = getmaxx(p_mainWin) - ram_width;
    int logHeight = getmaxy(p_mainWin) - sysinfo_height - log_top_offset;
    int logOriginY = log_top_offset;
    int logOriginX = 0;

    // TODO: make a function for building windows

    // Log border
    WINDOW *p_logOuterWin = newwin(logHeight, logWidth, logOriginY, logOriginX);
    box(p_logOuterWin, 0, 0);
    mvwprintw(p_logOuterWin, 0, 1, " Log ");
    wrefresh(p_logOuterWin);

    // Log window
    WINDOW *p_logWin =
        newwin(logHeight - 2, logWidth - 2, logOriginY + 1, logOriginX + 1);
    scrollok(p_logWin, true);
    wrefresh(p_logWin);

    // RAM window
    WINDOW *p_ramWin = newwin(logHeight, ram_width, logOriginY, logWidth);
    box(p_ramWin, 0, 0);
    mvwprintw(p_ramWin, 0, 1, " RAM Browser ");
    wrefresh(p_ramWin);

    // System state window
    WINDOW *p_stateWin = newwin(sysinfo_height, getmaxx(p_mainWin),
                                logOriginY + logHeight, logOriginX);
    box(p_stateWin, 0, 0);
    mvwprintw(p_stateWin, 0, 1, " System status ");
    wrefresh(p_stateWin);

    this->p_logWin = p_logWin;
    this->p_ramWin = p_ramWin;
    this->p_stateWin = p_stateWin;
};

void Debugger::displayLogMessage(const char *p_message) {
    wprintw(this->p_logWin, "%s\n", p_message);
    wrefresh(this->p_logWin);
};

WINDOW *Debugger::getLogWindow() { return p_logWin; };

void Debugger::updateWindows() {
    endwin();
    refresh();
    resizeterm(getmaxy(this->p_mainWin), getmaxx(this->p_mainWin));
    wrefresh(this->p_logWin);
    wrefresh(this->p_ramWin);
    wrefresh(this->p_stateWin);
    refresh();
}