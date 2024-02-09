#include "debugger.hpp"
#include "logger.hpp"
#include <iostream>
#include <ncurses.h>
using namespace std;

int main() {

  LoggerProxy log = Logger::getLoggerProxy("MAIN");

  try {

    Debugger debugger;

    log.setPrintTarget(debugger.getLogWindow());
    log.log("Ceci est un message de debug", LogLevel::debug);
    log.log("Ceci est un message d'information", LogLevel::info);
    log.log("Ceci est un message d'avertissement", LogLevel::warning);
    log.log("Ceci est un message d'erreur", LogLevel::error);

    getch();
    return 0;

  } catch (const char *err) {
    std::cerr << err << std::endl;
    return 0;
  }
}