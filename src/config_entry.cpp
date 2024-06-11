#include "config_entry.hpp"

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "logger.hpp"

using std::function;
using std::string;
using std::unordered_map;
using std::vector;

IdLogger logConfEnt = Logger::newIdLogger("CONFIG_ENTRY");

template <typename T>
ConfigEntry<T>::ConfigEntry(string id, T defaultValue,
                            function<bool(T)> validator) {
    if (!validator(defaultValue)) {
        logConfEnt
            << "Default value of '" << id
            << "' does not pass validator.\n    Value or validator might be "
               "incorrect.";
        logConfEnt.flushSsLog(LogLevel::error);
    }

    this->id = id;
    this->defaultValue = defaultValue;
    this->currentValue = defaultValue;
    this->validator = validator;
    logConfEnt << "New config member '" << id << "' added !";
    logConfEnt.flushSsLog();
}

template <typename T>
void ConfigEntry<T>::set(T value) {
    if (!this->validator(value)) {
        logConfEnt << "Couldn't set new value of '" << this->id
                   << "'.\n    Validator failed, set ignored.";
        logConfEnt.flushSsLog(LogLevel::error);
        return;
    }

    this->currentValue = value;
}

template <typename T>
void ConfigEntry<T>::reset() {
    this->currentValue = this->defaultValue;
}

template <typename T>
T ConfigEntry<T>::get() {
    return this->currentValue;
}

template <typename T>
string ConfigEntry<T>::getId() {
    return this->id;
}