#include "config.hpp"

#include <sstream>
#include <unordered_map>

#include "logger.hpp"

IdLogger logConf = Logger::newIdLogger("CONFIG");

using std::pair;
using std::string;
using std::unordered_map;

Config::Config(const vector<ConfigEntry<unsigned int>>& intEntries,
               const vector<ConfigEntry<string>>& stringEntries)
    : errorString("Error", ""), errorInt("Error", 0) {
    this->addIntsEntries(intEntries);
    this->addStringEntries(stringEntries);
    logConf.logCStr("Config created !");
}

Config::~Config() { logConf.logCStr("Config destroyed !", LogLevel::warning); }

ConfigEntry<string>& Config::stringEntry(string id) {
    auto pos = this->stringMap.find(id);
    if (pos != this->stringMap.end()) {
        return pos->second;
    }
    logConf
        << "Config member '" << id
        << "' requested but doesn't exist ! \n Returning error config member.";
    logConf.flushSsLog(LogLevel::error);
    return this->errorString;
}

ConfigEntry<unsigned int>& Config::intEntry(string id) {
    auto pos = this->intMap.find(id);
    if (pos != this->intMap.end()) {
        return pos->second;
    }
    logConf
        << "Config member '" << id
        << "' requested but doesn't exist ! \n Returning error config member.";
    logConf.flushSsLog(LogLevel::error);
    return this->errorInt;
}

void Config::addStringEntries(const vector<ConfigEntry<string>>& entries) {
    for (ConfigEntry<string> i : entries) {
        this->stringMap.insert(pair<string, ConfigEntry<string>>(i.getId(), i));
    }
}

void Config::addIntsEntries(const vector<ConfigEntry<unsigned int>>& entries) {
    for (ConfigEntry<unsigned int> i : entries) {
        this->intMap.insert(
            pair<string, ConfigEntry<unsigned int>>(i.getId(), i));
    }
}
