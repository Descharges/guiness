#include "wram.hpp"
#include "logger.hpp"
#include <cstdint>

auto logWRam = Logger::newLoggerProxy("WRAM");

WRam::WRam() {
  logWRam.logCStr("WRAM initialized", LogLevel::info);
}

WRam::~WRam() { logWRam.logCStr("WRAM destroyed", LogLevel::warning); }

uint8_t WRam::read(uint16_t addr) {
  if (addr >= 0x800) {
    logWRam.logCStr("Read out of bounds in RAM, returning 0", LogLevel::error);
    return 0;
  } else {
    return this->ram[addr];
  }
}

void WRam::write(uint8_t value, uint16_t addr) {
  if (addr >= 0x800) {
    logWRam.logCStr("Write out of bounds in RAM", LogLevel::error);
  } else {
    this->ram[addr] = value;
  }
}

uint16_t WRam::getSize() { return 0x800; }
