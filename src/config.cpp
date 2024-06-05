#include "config.hpp"

#include <sstream>
#include <unordered_map>

#include "logger.hpp"

IdLogger logConf = Logger::newIdLogger("CONFIG");

using std::unordered_map;
using std::string;

const unordered_map<string, string> defaultConfigMap = {
    {"FPS", "60"},
    {"BREAK_MODE", "NONE"},  // {NONE, FRAME, STEP}
    {"DEBUGGER", "TRUE"}};
;

Config::Config(unordered_map<string, string> const &initConfig) {
    this->configMap = initConfig;
}

Config *Config::defaultConfig() {
    unordered_map<string, string> defaultConf = defaultConfigMap;

    return new Config(defaultConf);
}

Config *Config::configFromFile(string const &path) { throw "Not implemented"; }

Config *Config::configFromArgs(int argc, char *argv[]) {
    throw "Not implemented";
}

Config::~Config() {}

bool Config::exists(string const &id) {
    auto it = configMap.find(id);

    if (it == this->configMap.end()) {
        return false;
    };

    return true;
}

void Config::set(string const &id, string const &value) {
    if (exists(id)) {
        this->configMap[id] = value;
        return;
    }

    logConf.getStringStream()
        << "Attempt to set unexisting config member : " << id;
    logConf.flushSsLog(error);
}

string Config::get(string const &id) {
    if (exists(id)) {
        return this->configMap[id];
    }

    logConf.getStringStream()
        << "Attempt to get unexisting config member : " << id;
    logConf.flushSsLog(error);
    return "";
}

bool Config::getAsBool(string const &id) {
    throw "Config::getAsBool is not implemented yet.";
}

unsigned int Config::getAsUInt(string const &id) {
    throw "Config::getAsUInt is not implemented yet.";
}

void Config::logConfig() {
    logConf << "\n\n"
            << "Configuration" << "\n-------------------";
    for (const auto &i : configMap) {
        logConf << "\n" << i.first << "-->" << i.second;
    }
    logConf << "\n";
    logConf.flushSsLog();
}
