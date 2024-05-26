#include "wram.hpp"

#include <cstdint>
#include <sstream>

#include "logger.hpp"

auto logWRam = Logger::newIdLogger("WRAM");

WRam::WRam() { logWRam.logCStr("WRAM initialized", LogLevel::info); }

WRam::~WRam() { logWRam.logCStr("WRAM destroyed", LogLevel::warning); }

uint8_t WRam::read(uint16_t addr) {
    if (addr >= 0x800) {
        logWRam.logCStr("Read out of bounds in RAM, returning 0",
                        LogLevel::error);
        return 0;
    } else {
        logWRam << "Reading " << Logger::formatHex8(this->ram[addr])
                << " at address " << Logger::formatHex16(addr);
        logWRam.flushSsLog();
        return this->ram[addr];
    }
}

void WRam::write(uint8_t value, uint16_t addr) {
    if (addr >= 0x800) {
        logWRam.logCStr("Write out of bounds in RAM", LogLevel::error);
    } else {
        logWRam << "Writing " << Logger::formatHex8(value) << " at address "
                << Logger::formatHex16(addr);
        logWRam.flushSsLog();
        this->ram[addr] = value;
    }
}

uint16_t WRam::getSize() { return 0x800; };
uint16_t WRam::getLocation() { return 0x0000; }
