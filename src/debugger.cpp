#include "debugger.hpp"
#include <iostream>
#include <ncurses.h>

Debugger::Debugger(){

    // Create main window
    const WINDOW *mainWin = initscr();
    mvprintw(0, 0, "GuiNESs debugger");

    //Create logging window
    WINDOW *logWin = newwin(getmaxy(mainWin)-2, getmaxx(mainWin), 2, 0);
    refresh();
    box(logWin, 0, 0);
    mvwprintw(logWin, 0, 1, "[log]");
    mvwprintw(logWin, 2, 2, "Debbuger initialized !");
    wrefresh(logWin);
};

Debugger::~Debugger(){
    endwin();
    std::cout << "Debugger destroyed :D" << std::endl;
}