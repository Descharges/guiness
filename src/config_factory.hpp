#ifndef CONFIGFACTORY_H
#define CONFIGFACTORY_H

#include "config.hpp"

class ConfigFactory {
public:
  static Config defaultConfig();
  static Config configFromFile(std::string const &path);
  static Config configFromArgs(int argc, char *argv[]);

private:
  Config configFromMap(std::unordered_map<std::string, std::string> const &configMap);
};

#endif