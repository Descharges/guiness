#include "config_factory.hpp"
#include "config.hpp"
#include <unordered_map>

Config ConfigFactory::defaultConfig() {
  std::unordered_map<std::string, std::string> defaultConfigMap;
  defaultConfigMap = {{"ROM", ""},
                      {"FPS", "60"},
                      {"RUN_MODE", "AUTO"},
                      {"DEBUG", "true"},
                      {"LOG_LEVEL", "3"}};
  return Config(defaultConfigMap);
}

Config ConfigFactory::configFromFile(std::string const &path) {
  throw "ConfigFactory::configFromFile is not implemented yet.";
}

Config ConfigFactory::configFromArgs(int argc, char *argv[]) {
  throw "ConfigFactory::configFromArgs is not implemented yet.";
}

Config ConfigFactory::configFromMap(
    std::unordered_map<std::string, std::string> const &configMap) {
  auto conf = Config(defaultConfig());
  for (const auto &i : configMap) {
    if (conf.exists(i.first)) {
      conf.set(i.first, i.second);
    }
  }
  return conf;
}