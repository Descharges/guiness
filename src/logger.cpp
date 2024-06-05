#include "logger.hpp"

#include <ncurses.h>

#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <streambuf>

using std::hex;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;
using std::uppercase;

// Logger
Logger Logger::s_instance;

Logger::Logger(){};

IdLogger Logger::newIdLogger(const char *p_id) {
    return IdLogger(p_id, Logger::s_instance);
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

IdLogger::IdLogger(const char *p_id, Logger &logger)
    : logger(logger), p_id(p_id) {}

void IdLogger::logCStr(const char *p_logMessage, LogLevel lvl) {
    logger.printLogMessage(p_id, p_logMessage, lvl);
}

void IdLogger::logStr(string logMessage, LogLevel lvl) {
    this->logCStr(logMessage.c_str(), lvl);
}

void IdLogger::logSStream(stringstream &logStream, LogLevel lvl) {
    this->logStr(logStream.str(), lvl);
}

void IdLogger::setPrintTarget(WINDOW *p_targetWindow) {
    logger.setPrintTarget(p_targetWindow);
};

stringstream &IdLogger::getStringStream() { return this->sslog; }

void IdLogger::flushSsLog(LogLevel lvl) {
    this->logSStream(this->sslog, lvl);
    sslog.str("");
}

IdLogger &IdLogger::operator<<(const char *p_cStr) {
    sslog << p_cStr;
    return *this;
}

IdLogger &IdLogger::operator<<(string str) {
    sslog << str;
    return *this;
}

string Logger::formatHex8(uint8_t n) {
    stringstream ssout;
    ssout << "0x" << uppercase << setfill('0') << setw(2) << hex << unsigned(n);
    return ssout.str();
}

string Logger::formatHex16(uint16_t n) {
    stringstream ssout;
    ssout << "0x" << uppercase << setfill('0') << setw(4) << hex << unsigned(n);
    return ssout.str();
}
// i >
// D >
// ! >
// X | Dummy >