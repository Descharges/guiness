#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <ncurses.h>

#define HEADER_PAIR 1
#define WARN_PAIR 2
#define ERR_PAIR 3
#define DEFAULT_PAIR 4
#define INFO_PAIR 5
#define MIN_LOG_HEIGHT 10
#define MIN_LOG_WIDTH 68
#define LOG_TOP_OFFSET 2
#define SYSTEM_STATUS_HEIGHT 5
#define RAM_BROWSER_WIDTH 34

class Debugger {

public:
  Debugger();
  ~Debugger();
  void displayLogMessage(const char *p_message);
  void updateWindows();
  WINDOW *getLogWindow();

private:
  WINDOW *p_mainWin;
  WINDOW *p_logWin;
  WINDOW *p_stateWin;
  WINDOW *p_ramWin;
  WINDOW *getLargeWindow();
  void checkColorDisponibility(WINDOW *p_mainWindow);
  void initColors();
  void initHeader();
  void initWindows(WINDOW *p_mainWindow, int ram_width, int cpu_height,
                   int log_top_offset);
};

#endif