#include "bus.hpp"
#include "logger.hpp"
#include <cstdint>
#include <ios>
#include <list>
#include <memory>
#include <sstream>
#include <string>

using std::list;
using std::shared_ptr;
using std::string;
using std::stringstream;

LoggerProxy logBus = Logger::newLoggerProxy("BUS");

template <typename addr_t, typename data_t> Bus<addr_t, data_t>::Bus() {
  this->deviceList = list<PluggedDevice<addr_t, data_t>>();
  logBus.logCStr("Device bus initialized");
}

template <typename addr_t, typename data_t> Bus<addr_t, data_t>::~Bus() {
  logBus.logCStr("Device bus destroyed", LogLevel::warning);
}

template <typename addr_t, typename data_t>
void Bus<addr_t, data_t>::addDevice(
    addr_t startAddr, shared_ptr<BusDevice<addr_t, data_t>> p_device) {
  PluggedDevice<addr_t, data_t> newDevice;
  newDevice.device = p_device;
  newDevice.address = startAddr;
  this->deviceList.push_front(newDevice);

  std::stringstream ssout;
  ssout << "Added device of type " << typeid(*p_device).name() << " at address "
        << Logger::formatHex16bits(startAddr);
  logBus.logSStream(ssout);
}

template <typename addr_t, typename data_t>
data_t Bus<addr_t, data_t>::read(addr_t addr) {
  for (PluggedDevice<addr_t, data_t> const &i : this->deviceList) {
    if (addr >= i.address && addr <= i.address + i.device->getSize()) {
      return i.device->read(addr);
    }
  }
  logBus.logCStr(
      "Open bus behaviour : address doesn't have any devices asscoiated to it",
      LogLevel::error);
  return 0xff;
};

/** Bus template with 16 bits address and 8 bits values*/
template class Bus<uint16_t, uint8_t>;

/** BusDevice template with 16 bits address and 8 bits values*/
template class BusDevice<uint16_t, uint8_t>;