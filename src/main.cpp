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

int main()
{
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
        auto config = shared_ptr<Config>(new Config());

        logMain.logStr(std::to_string(config->FPS));

        // Boucle d'événements
        bool quit = false;
        SDL_Event e;
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            SDL_Delay(16);
        }
    }

    return 0;
}
