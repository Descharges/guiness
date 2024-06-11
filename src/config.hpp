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
    /**
     * @brief Construct a new Config object
     *
     */
    Config(const vector<ConfigEntry<unsigned int>>& intEntries,
           const vector<ConfigEntry<string>>& stringEntries);

    /**
     * @brief Destroy the Config object
     *
     */
    ~Config();

    /**
     * @brief Get a string config entry
     *
     * @param id
     * @return ConfigEntry<string>& The config entry
     */
    ConfigEntry<string>& stringEntry(string id);

    /**
     * @brief Get an int config entry
     *
     * @param id
     * @return ConfigEntry<unsigned int>& The config entry
     */
    ConfigEntry<unsigned int>& intEntry(string id);

   private:
    /**
     * @brief Add new string entries to the Config
     *
     * @param entries The entries to be added
     */
    void addStringEntries(const vector<ConfigEntry<string>>& entries);

    /**
     * @brief Add new int entries to the Config
     *
     * @param entries
     */
    void addIntsEntries(const vector<ConfigEntry<unsigned int>>& entries);

    unordered_map<string, ConfigEntry<string>> stringMap;
    unordered_map<string, ConfigEntry<unsigned int>> intMap;
    ConfigEntry<string> errorString;
    ConfigEntry<unsigned int> errorInt;
};

#endif