#include "bus.hpp"

#include <cstdint>
#include <ios>
#include <list>
#include <memory>
#include <sstream>
#include <string>

#include "logger.hpp"

using std::list;
using std::shared_ptr;
using std::string;
using std::stringstream;

IdLogger logBus = Logger::newIdLogger("BUS");

template <typename addr_t, typename data_t>
Bus<addr_t, data_t>::Bus() {
    this->deviceList = list<shared_ptr<BusDevice<addr_t, data_t>>>();
    logBus.logCStr("Device bus initialized", LogLevel::info);
}

template <typename addr_t, typename data_t>
Bus<addr_t, data_t>::~Bus() {
    logBus.logCStr("Device bus destroyed", LogLevel::warning);
}

template <typename addr_t, typename data_t>
void Bus<addr_t, data_t>::addDevice(
    shared_ptr<BusDevice<addr_t, data_t>> p_device) {
    this->deviceList.push_front(p_device);

    logBus << "Added device of type " << typeid(*p_device).name()
           << " at address " << Logger::formatHex16(p_device->getLocation());
    logBus.flushSsLog();
}

template <typename addr_t, typename data_t>
data_t Bus<addr_t, data_t>::read(addr_t addr) {
    for (shared_ptr<BusDevice<addr_t, data_t>> const &i :
         this->deviceList) {
        if (addr >= i->getLocation() &&
            addr <= i->getLocation() + i->getSize()) {
            return i->read(addr);
        }
    }
    logBus.logCStr(
        "Open bus behaviour : address doesn't have any devices asscoiated to "
        "it",
        LogLevel::error);
    return 0xff;
};

template <typename addr_t, typename data_t>
void Bus<addr_t, data_t>::write(data_t value, addr_t addr) {
    for (shared_ptr<BusDevice<addr_t, data_t>> const &i :
         this->deviceList) {
        if (addr >= i->getLocation() &&
            addr <= i->getLocation() + i->getSize()) {
            i->write(value, addr);
            return;
        }
    }
    logBus.logCStr(
        "Open bus behaviour : address doesn't have any devices asscoiated to "
        "it",
        LogLevel::error);
};

/** Bus template with 16 bits address and 8 bits values*/
template class Bus<uint16_t, uint8_t>;

/** BusDevice template with 16 bits address and 8 bits values*/
template class BusDevice<uint16_t, uint8_t>;