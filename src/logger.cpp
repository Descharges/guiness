#include "logger.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <streambuf>
// Logger

Logger Logger::s_instance;

Logger::Logger(){};

LoggerProxy Logger::newLoggerProxy(const char *p_id) {
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
      prefix = "D";
      color_pair = DEFAULT_PAIR;
      break;
    case info:
      prefix = "i";
      color_pair = INFO_PAIR;
      break;
    case warning:
      prefix = "!";
      color_pair = WARN_PAIR;
      break;
    case error:
      prefix = "X";
      color_pair = ERR_PAIR;
      break;
    }

    wattron(p_displayWindow, COLOR_PAIR(color_pair));
    wprintw(p_displayWindow, "%s | %s > %s\n", prefix, p_id, p_message);
    wrefresh(p_displayWindow);
    wattroff(p_displayWindow, COLOR_PAIR(color_pair));

  } else {
    std::cout << p_id << " - " << p_message << std::endl;
  }
};

// Logger proxy

LoggerProxy::LoggerProxy(const char *p_id, Logger &logger)
    : logger(logger), p_id(p_id) {}

void LoggerProxy::logCStr(const char *p_logMessage, LogLevel lvl) {
  logger.printLogMessage(p_id, p_logMessage, lvl);
}

void LoggerProxy::logStr(std::string logMessage, LogLevel lvl) {
  this->logCStr(logMessage.c_str(), lvl);
}

void LoggerProxy::logSStream(std::stringstream &logStream, LogLevel lvl) {
  this->logStr(logStream.str(), lvl);
}

void LoggerProxy::setPrintTarget(WINDOW *p_targetWindow) {
  logger.setPrintTarget(p_targetWindow);
};

std::stringstream &LoggerProxy::getStringStream(){
  return this->sslog;
}

void LoggerProxy::flushSsLog(LogLevel lvl){
  this->logSStream(this->sslog, lvl);
  sslog.str("");
}

LoggerProxy &LoggerProxy::operator<<(const char *p_cStr){
  sslog << p_cStr;
  return *this;
}

LoggerProxy &LoggerProxy::operator<<(std::string str){
  sslog << str;
  return *this;
}

std::string Logger::formatHex8(uint8_t n) {
  std::stringstream ssout;
  ssout << "0x" << std::uppercase << std::setfill('0') << std::setw(2)
        << std::hex << unsigned(n);
  return ssout.str();
}

std::string Logger::formatHex16(uint16_t n) {
  std::stringstream ssout;
  ssout << "0x" << std::uppercase << std::setfill('0') << std::setw(4)
        << std::hex << unsigned(n);
  return ssout.str();
}
// i >
// D >
// ! >
// X | Dummy >