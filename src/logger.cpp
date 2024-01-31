#include "logger.hpp"
#include <iostream>
#include <ncurses.h>

// Logger

Logger Logger::s_instance;

Logger::Logger(){};

LoggerProxy Logger::getLoggerProxy(const char *p_id) {
  return LoggerProxy(p_id, Logger::s_instance);
};

void Logger::setPrintTarget(WINDOW *p_targetWindow) {
  this->p_displayWindow = p_targetWindow;
};

void Logger::printLogMessage(const char *p_id, const char *p_message,
                             LogLevel lvl) {
  if (p_displayWindow) {

    const char *prefix;
    int color_pair;

    switch (lvl) {
    case debug:
      prefix = "<D>";
      color_pair = DEFAULT_PAIR;
      break;
    case info:
      prefix = "(i)";
      color_pair = INFO_PAIR;
      break;
    case warning:
      prefix = "/!\\";
      color_pair = WARN_PAIR;
      break;
    case error:
      prefix = "[X]";
      color_pair = ERR_PAIR;
      break;
    }

    wattron(p_displayWindow, COLOR_PAIR(color_pair));
    wprintw(p_displayWindow, "[%s] %s %s\n", p_id, prefix, p_message);
    wrefresh(p_displayWindow);
    wattroff(p_displayWindow, COLOR_PAIR(color_pair));

  } else {
    std::cout << p_id << " - " << p_message << std::endl;
  }
};

// Logger proxy

LoggerProxy::LoggerProxy(const char *p_id, Logger &logger)
    : logger(logger), p_id(p_id) {}

void LoggerProxy::log(const char *p_logMessage, LogLevel lvl) {
  logger.printLogMessage(p_id, p_logMessage, lvl);
}

void LoggerProxy::setPrintTarget(WINDOW *p_targetWindow) {
  logger.setPrintTarget(p_targetWindow);
};