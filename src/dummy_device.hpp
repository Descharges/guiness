#ifndef DUMMYDEV_H
#define DUMMYDEV_H

#include <cstdint>

#include "bus.hpp"

/**
 * @brief Dummy bus device using NES address & data length (16 & 8 bits).
 * Used for test purposes
 *
 */
class DummyBusDevice : public BusDevice<uint16_t, uint8_t> {
   public:
    /**
     * @brief Construct a new Dummy Bus Device object
     *
     */
    DummyBusDevice();

    /**
     * @brief Destroy the Dummy Bus Device object
     *
     */
    ~DummyBusDevice();

    uint8_t read(uint16_t addr);
    void write(uint8_t value, uint16_t addr);
    uint16_t getSize();
};

#endif