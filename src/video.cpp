#include "video.hpp"

#include "logger.hpp"

IdLogger logVideo = Logger::newIdLogger("VIDEO");

Video::Video(int width, int height) {
    // Init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw "Couldn't initialize SDL";
    }

    // Init Window
    this->window = SDL_CreateWindow(
        "Guiness - NES Emulator", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    // Check if window opened properly
    if (this->window == nullptr) {
        throw "Window couldn't be opened";
    }
    logVideo.logStr("Video initialized !", LogLevel::info);
}

Video::~Video() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    logVideo.logStr("Video destroyed !", LogLevel::warning);
}
