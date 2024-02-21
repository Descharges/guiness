#include "bus.hpp"
#include "debugger.hpp"
#include "logger.hpp"
#include "dummy_device.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <ncurses.h>

using std::shared_ptr;

int main() {

  LoggerProxy logMain = Logger::newLoggerProxy("MAIN");

  Debugger debugger;
  logMain.setPrintTarget(debugger.getLogWindow());

  {
    auto p_bus = shared_ptr<Bus<uint16_t, uint8_t>>(new Bus<uint16_t, uint8_t>());
    auto p_device = shared_ptr<DummyBusDevice>(new DummyBusDevice());
    p_bus->addDevice(0xFFFE, p_device);
    p_bus->read(0xFFFD);
    p_bus->read(0xFFFE);
    p_bus->read(0xFFFF);
  }

  while (1) {
  }

  return 0;
}
