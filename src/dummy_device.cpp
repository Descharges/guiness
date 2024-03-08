#include "dummy_device.hpp"
#include "bus.hpp"
#include "logger.hpp"
#include <sstream>
#include <string>

LoggerProxy logDummy = Logger::newLoggerProxy("DUMMY");

DummyBusDevice::DummyBusDevice() { logDummy.logCStr("Dummy initialized"); }

DummyBusDevice::~DummyBusDevice() {
  logDummy.logCStr("Dummy Destroyed", LogLevel::warning);
}

uint8_t DummyBusDevice::read(uint16_t addr) {
  logDummy.getStringStream() << "Read to dummy at address $" << Logger::formatHex16bits(addr);
  logDummy.flushSsLog();
  return 255;
};

void DummyBusDevice::write(uint8_t value, uint16_t addr) {
  logDummy.getStringStream() << "Write " << Logger::formatHex8bits(value) << " to dummy at address "
        << Logger::formatHex16bits(addr);
  logDummy.flushSsLog();
}

uint16_t DummyBusDevice::getSize() { return 1; };