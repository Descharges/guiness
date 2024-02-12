#include "bus.hpp"
#include "logger.hpp"
#include <cstdint>
#include <list>
#include <memory>
using std::list;
using std::shared_ptr;

LoggerProxy logBus = Logger::getLoggerProxy("BUS");

template <typename addr_t, typename data_t> Bus<addr_t, data_t>::Bus() {
  this->deviceList = list<pluggedDevice<addr_t, data_t>>();
  logBus.log("Device bus initialized");
}

template <typename addr_t, typename data_t> Bus<addr_t, data_t>::~Bus(){
  logBus.log("Device bus destroyed", LogLevel::warning);
}

template <typename addr_t, typename data_t>
void Bus<addr_t, data_t>::addDevice(
    addr_t startAddr, shared_ptr<BusDevice<addr_t, data_t>> p_device) {
  pluggedDevice<addr_t, data_t> newDevice;
  newDevice.device = p_device;
  newDevice.address = startAddr;
  this->deviceList.push_front(newDevice);
}

template <typename addr_t, typename data_t>
data_t read(addr_t addr){

};

template class Bus<uint16_t, uint8_t>;
