#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <cstring>
#include <list>
#include <memory>

using std::list;
using std::shared_ptr;
using std::string;

/**
 * @brief Abstract type used to represent a device which can be plugged in a
 * bus. A bus device can be read and write to at specific address. It can only
 * be "plugged in" to a bus using the same address and data types.
 *
 * @tparam addr_t The type used to represent adresse
 * @tparam data_t The type of the data the device will return
 */
template <typename addr_t, typename data_t> class BusDevice {

public:
  /**
   * @brief Read a value at a certain address
   *
   * @param addr the address to be read
   * @return data_t The read value
   */
  virtual data_t read(addr_t addr) = 0;

  /**
   * @brief Write a value to a certain address
   *
   * @param value The value to write
   * @param addr  The address to write the value to
   */
  virtual void write(data_t value, addr_t addr) = 0;

  /**
   * @brief Get the number of addresses the devices occupies.
   *
   * @return addr_t The number of addresses
   */
  virtual addr_t getSize() = 0;
};

/**
 * @brief Structure with a bus device, and the first address at which the device
 * is "Plugged in".
 * eg : A device of size 10 plugged at the address 5 will see
 * read from address 5 to 14 frowarded to it.
 *
 * @tparam addr_t The type used to represent adresse
 * @tparam data_t The type of the data the device will return
 */
template <typename addr_t, typename data_t> struct PluggedDevice {

  /** Shared pointer to a device*/
  shared_ptr<BusDevice<addr_t, data_t>> device;

  /** The adress at which it is plugged in*/
  addr_t address;
};

/**
 * @brief Redirects read and write request on an address space to different
 * devices
 *
 * @tparam addr_t The type used to represent adresse
 * @tparam data_t The type of the data the device will return
 */
template <typename addr_t, typename data_t> class Bus {

public:
  /**
   * @brief Construct a new Bus object
   *
   */
  Bus();

  /**
   * @brief Destroy the Bus object
   *
   */
  ~Bus();

  /**
   * @brief Forwards read request at the device connected to this address.
   *
   * @param addr the address to be read
   * @return data_t The read value
   */
  data_t read(addr_t addr);

  /**
   * @brief Forwards write request at the device connected to this address.
   *
   * @param value The value to write
   * @param addr  The address to write the value to
   */
  void write(data_t value, addr_t addr);
  void addDevice(addr_t startAddr,
                 shared_ptr<BusDevice<addr_t, data_t>> p_device);

private:
  list<PluggedDevice<addr_t, data_t>> deviceList;
};

#endif