#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

/**
 * @brief Stores the configuration of the application.
 *
 * Acts as a wrapper around a map with key and values as string, but with
 * options to cast and with checks to forbid the addition of new members
 * after object creation.
 */
class Config {
   public:
    /**
     * @brief Construct a new Config object
     *
     */
    Config(unordered_map<string, string> const &defaultConfig);

    /**
     * @brief Returns a new Config with default values
     */
    static Config *defaultConfig();

    /**
     *
     */
    static Config *configFromFile(string const &path);

    /**
     *
     */
    static Config *configFromArgs(int argc, char *argv[]);

    /**
     * @brief Destroy the Config object
     *
     */
    ~Config();

    /**
     * @brief Checks if an id is a config member.
     *
     * @param id The id to check
     * @return true The id is a member of the configuration
     * @return false The id is not a member of the configuration
     */
    bool exists(string const &id);

    /**
     * @brief Sets the value of a configuration member.
     *
     * @param id The id of the member.
     * @param value The value to set.
     */
    void set(string const &id, string const &value);

    /**
     * @brief Gets the value of a configuration member.
     *
     * @param id The id of the member.
     * @return string The value of the member. Empty string if the member
     * is not found.
     */
    string get(string const &id);

    /**
     * @brief Get a member of configuration and casts it as a boolean
     */
    bool getAsBool(string const &id);

    /**
     * @brief Get a member of configuration and casts it as an unsigned int
     */
    unsigned int getAsUInt(string const &id);

    /**
     * @brief Logs the config
     *
     */
    void logConfig();

   private:
    /** Stores string config members*/
    unordered_map<string, string> configMap;
};

#endif