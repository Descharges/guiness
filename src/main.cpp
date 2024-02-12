#include "bus.hpp"
#include "debugger.hpp"
#include "logger.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <ncurses.h>

using std::shared_ptr;

int main() {

  LoggerProxy logMain = Logger::getLoggerProxy("MAIN");

  Debugger debugger;

  logMain.setPrintTarget(debugger.getLogWindow());
  logMain.log("Ceci est un message de debug", LogLevel::debug);
  logMain.log("Ceci est un message d'information", LogLevel::info);
  logMain.log("Ceci est un message d'avertissement", LogLevel::warning);
  logMain.log("Ceci est un message d'erreur", LogLevel::error);

  {
    auto bus = shared_ptr<Bus<uint16_t, uint8_t>>(new Bus<uint16_t, uint8_t>());
  }

  while (1) {
  }

  return 0;
}
