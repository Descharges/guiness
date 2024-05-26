#ifndef WRAM_H
#define WRAM_H

#include <array>
#include <cstdint>

#include "bus.hpp"

/**
 * @brief Work ram of the NES.
 *
 * Holds an array of values representing ram content
 *
 */
class WRam : public BusDevice<uint16_t, uint8_t> {
   public:
    /**
     * @brief Construct a new WRam object
     *
     */
    WRam();

    /**
     * @brief Destroy the WRam object
     *
     */
    ~WRam();

    /**
     * @brief Reads value from WRAM
     *
     * @param addr The adress to read from
     * @return uint8_t The value at the adress
     */
    uint8_t read(uint16_t addr);

    /**
     * @brief Write values to RAM
     *
     * @param value The value to write
     * @param addr The addrss to write to
     */
    void write(uint8_t value, uint16_t addr);

    /**
     * @brief Get the size of the RAM
     *
     * @return uint16_t
     */
    uint16_t getSize();

    /**
     * @brief Get the location of the RAM
     *
     * @return uint16_t
     */
    uint16_t getLocation();

   private:
    /**
     * @brief The array representing RAM
     *
     */
    uint8_t ram[0x800] = {0};
};

#endif