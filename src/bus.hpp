#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <list>
#include <memory>

using std::list;
using std::shared_ptr;

template <typename addr_t, typename data_t> class BusDevice {

public:
  virtual data_t read(addr_t addr) = 0;
  virtual void write(data_t value, addr_t addr) = 0;
  virtual addr_t getSize() = 0;
};

template <typename addr_t, typename data_t> struct pluggedDevice {
  shared_ptr<BusDevice<addr_t, data_t>> device;
  addr_t address;
};

template <typename addr_t, typename data_t> class Bus {

public:
  Bus();
  ~Bus();
  data_t read(addr_t addr);
  void write(data_t value, addr_t addr);
  void addDevice(addr_t startAddr, shared_ptr<BusDevice<addr_t, data_t>> p_device);

private:
  list<pluggedDevice<addr_t, data_t>> deviceList;
};

#endif