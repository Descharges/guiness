#include <ncurses.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>

#include "bus.hpp"
#include "config.hpp"
#include "debugger.hpp"
#include "logger.hpp"
#include "wram.hpp"

using std::shared_ptr;

int main() {
    IdLogger logMain = Logger::newIdLogger("MAIN");

    Debugger debugger;
    logMain.setPrintTarget(debugger.getLogWindow());

    {
        auto p_bus =
            shared_ptr<Bus<uint16_t, uint8_t>>(new Bus<uint16_t, uint8_t>());
        auto p_wram = shared_ptr<WRam>(new WRam());
        p_bus->addDevice(p_wram);

        p_bus->write(0x21, 0x0000);
        p_bus->read(0x0000);

        auto config = shared_ptr<Config>(Config::defaultConfig());
        config->logConfig();
        logMain << "Cringe";
    }

    while (1) {
    }

    return 0;
}
