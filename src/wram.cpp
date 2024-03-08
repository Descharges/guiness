#include "wram.hpp"
#include "logger.hpp"
#include <cstdint>
#include <sstream>

auto logWRam = Logger::newLoggerProxy("WRAM");

WRam::WRam() { logWRam.logCStr("WRAM initialized", LogLevel::info); }

WRam::~WRam() { logWRam.logCStr("WRAM destroyed", LogLevel::warning); }

uint8_t WRam::read(uint16_t addr) {
  if (addr >= 0x800) {
    logWRam.logCStr("Read out of bounds in RAM, returning 0", LogLevel::error);
    return 0;
  } else {
    std::stringstream ssout;
    ssout << "Reading " << Logger::formatHex8bits(this->ram[addr]) <<" at address " << Logger::formatHex16bits(addr);
    logWRam.logSStream(ssout);
    return this->ram[addr];
  }
}

void WRam::write(uint8_t value, uint16_t addr) {
  if (addr >= 0x800) {
    logWRam.logCStr("Write out of bounds in RAM", LogLevel::error);
  } else {
    std::stringstream ssout;
    ssout << "Writing " << Logger::formatHex8bits(value)<< " at address " << Logger::formatHex16bits(addr);
    logWRam.logSStream(ssout);
    this->ram[addr] = value;
  }
}

uint16_t WRam::getSize() { return 0x800; };
uint16_t WRam::getLocation() { return 0x0000;}
