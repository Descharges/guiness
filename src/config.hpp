#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

/**
 * @brief Stroes the configuration of the application.
 *
 * Acts as a wrapper around a map with key and values as string, but with
 * options to cast and with checks to forbid the addition of new memmbers
 * after object creation.
 */
class Config {
public:
  /**
   * @brief Construct a new Config object
   *
   */
  Config(std::unordered_map<std::string, std::string> const &defaultConfig);

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
  bool exists(std::string const &id);

  /**
   * @brief Sets the value of a configuration member.
   *
   * @param id The id of the member.
   * @param value The value to set.
   */
  void set(std::string const &id, std::string const &value);

  /**
   * @brief Gets the value of a configuration member.
   *
   * @param id The id of the member.
   * @return std::string The value of the member. Empty string if the member is
   * not found.
   */
  std::string get(std::string const &id);

  /**
   * @brief Get a member of configuration and casts it as a boolean
   */
  bool getAsBool(std::string const &id);

  /**
   * @brief Get a member of configuration and casts it as an unsigned int
   */
  unsigned int getAsUInt(std::string const &id);

  /**
   * @brief Logs the config
   *
   */
  void logConfig();

private:
  /** Strores string config members*/
  std::unordered_map<std::string, std::string> configMap;
};

#endif