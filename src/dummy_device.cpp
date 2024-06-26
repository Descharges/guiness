#include "dummy_device.hpp"

#include <sstream>
#include <string>

#include "bus.hpp"
#include "logger.hpp"

IdLogger logDummy = Logger::newIdLogger("DUMMY");

DummyBusDevice::DummyBusDevice() { logDummy.logCStr("Dummy initialized"); }

DummyBusDevice::~DummyBusDevice() {
    logDummy.logCStr("Dummy Destroyed", LogLevel::warning);
}

uint8_t DummyBusDevice::read(uint16_t addr) {
    logDummy << "Read to dummy at address $" << Logger::formatHex16(addr);
    logDummy.flushSsLog();
    return 255;
};

void DummyBusDevice::write(uint8_t value, uint16_t addr) {
    logDummy << "Write " << Logger::formatHex8(value) << " to dummy at address "
             << Logger::formatHex16(addr);
    logDummy.flushSsLog();
}

uint16_t DummyBusDevice::getSize() { return 1; };