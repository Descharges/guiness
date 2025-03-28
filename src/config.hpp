#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <vector>

#include "config_entry.hpp"

using std::string;
using std::unordered_map;
using std::vector;

class Config {
   public:
       /// @brief Creates a new config.
       Config();

       /// @brief Destroys the config.
       ~Config();

       /// The FPS count. 0 = unlimited.
       int FPS;

       /// If true, the user will have to enter a key to advance each frame;
       bool FrameToFrameMode;
};

#endif