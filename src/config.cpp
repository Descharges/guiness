#include "config.hpp"
#include "logger.hpp"
#include <sstream>

LoggerProxy logConf = Logger::newLoggerProxy("CONFIG");

Config::Config(
    std::unordered_map<std::string, std::string> const &defaultConfig) {
  this->configMap = defaultConfig;
}

Config::~Config() {}

bool Config::exists(std::string const &id) {
  auto it = configMap.find(id);

  if (it == this->configMap.end()) {
    return false;
  };

  return true;
}

void Config::set(std::string const &id, std::string const &value) {
  if (exists(id)) {
    this->configMap[id] = value;
    return;
  }

  logConf.getStringStream()
      << "Attempt to set unexisting config member : " << id;
  logConf.flushSsLog(error);
}

std::string Config::get(std::string const &id) {

  if (exists(id)) {
    return this->configMap[id];
  }

  logConf.getStringStream()
      << "Attempt to get unexisting config member : " << id;
  logConf.flushSsLog(error);
  return "";
}

bool Config::getAsBool(std::string const &id) {
  throw "Config::getAsBool is not implemented yet.";
}

unsigned int Config::getAsUInt(std::string const &id) {
  throw "Config::getAsUInt is not implemented yet.";
}

void Config::logConfig()
{
  logConf << "\n\n" << "Configuration" << "\n-------------------";
  for (const auto &i : configMap){
    logConf << "\n" << i.first << "-->" << i.second;
  }
  logConf << "\n";
  logConf.flushSsLog();
}