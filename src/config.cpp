#include "config.hpp"

#include <sstream>
#include <unordered_map>

#include "logger.hpp"

IdLogger logConf = Logger::newIdLogger("CONFIG");

Config::Config(){
    this->FPS = 60;
    this->FrameToFrameMode = true;
}

Config::~Config() { logConf.logCStr("Config destroyed !", LogLevel::warning); }
