#include "bus.hpp"
#include "debugger.hpp"
#include "logger.hpp"
#include "wram.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <sstream>

using std::shared_ptr;

int main() {

  LoggerProxy logMain = Logger::newLoggerProxy("MAIN");

  Debugger debugger;
  logMain.setPrintTarget(debugger.getLogWindow());

  {
    std::stringstream ssout;

    auto p_bus = shared_ptr<Bus<uint16_t, uint8_t>>(new Bus<uint16_t, uint8_t>());
    auto p_wram = shared_ptr<WRam>(new WRam());
    p_bus->addDevice(0x0000, p_wram);

    p_bus->write(0x21, 0x0000);
    ssout << "Read value at addr 0x0000 : " << Logger::formatHex8bits(p_bus->read(0x0000));
    logMain.logSStream(ssout);
    ssout.str("");
    
  }

  while (1) {
  }

  return 0;
}
