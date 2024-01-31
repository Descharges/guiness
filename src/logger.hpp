#ifndef LOGGER_H
#define LOGGER_H

#include <ncurses.h>

#define HEADER_PAIR 1
#define WARN_PAIR 2
#define ERR_PAIR 3
#define DEFAULT_PAIR 4
#define INFO_PAIR 5

enum LogLevel { debug, info, warning, error };

class LoggerProxy;

class Logger {

public:
  static LoggerProxy getLoggerProxy(const char *p_id);
  void setPrintTarget(WINDOW *p_targetWindow);
  void printLogMessage(const char *p_id, const char *p_message, LogLevel lvl);

private:
  Logger();
  static Logger s_instance;
  WINDOW *p_displayWindow = NULL;
};

class LoggerProxy {

public:
  void log(const char *p_logMessage, LogLevel lvl = info);
  LoggerProxy(const char *p_id, Logger &loggerInstance);
  void setPrintTarget(WINDOW *p_targetWindow);

private:
  const char *p_id;
  Logger &logger;
  LoggerProxy();
};

#endif