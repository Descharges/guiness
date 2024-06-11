#include <SDL2/SDL.h>
#include <ncurses.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>

#include "bus.hpp"
#include "config.hpp"
#include "config_entry.hpp"
#include "debugger.hpp"
#include "logger.hpp"
#include "video.hpp"
#include "wram.hpp"

using std::shared_ptr;
using std::string;

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

        auto p_video = shared_ptr<Video>(new Video(500, 500));

        const vector<ConfigEntry<unsigned int>>& defaultConfInt = {
            ConfigEntry<unsigned int>(
                "FPS", 60, [](int n) { return (n >= 0) && (n < 500); }),
            ConfigEntry<unsigned int>(
                "DEBUG_LEVEL", 0, [](int n) { return (n >= 0) && (n < 4); }),
        };

        const vector<ConfigEntry<string>>& defaultConfString = {};

        auto conf = Config(defaultConfInt, defaultConfString);

        conf.intEntry("FPS").set(40);
        logMain << std::to_string(conf.intEntry("FPS").get());
        logMain.flushSsLog();
        logMain << std::to_string(conf.intEntry("Prout").get());
        logMain.flushSsLog();

        // Boucle d'événements
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            SDL_Delay(16);
        }
    }

    return 0;
}
