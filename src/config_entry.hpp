#ifndef CONFIG_ENTRY_H
#define CONFIG_ENTRY_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

using std::function;
using std::string;
using std::unordered_map;
using std::vector;

template <typename T>
class ConfigEntry {
   public:
    /**
     * @brief Construct a new Config Entry object
     *
     * @param id The identifier of the entry
     * @param defaultValue The default value
     * @param validator The validator lambda (see doc)
     */
    ConfigEntry(
        string id, T defaultValue,
        function<bool(T)> validator = [](T n) { return true; });

    /**
     * @brief Get the Id object
     *
     * @return string
     */
    string getId();

    /**
     * @brief Get the value of the config entry
     *
     * @return T
     */
    T get();

    /**
     * @brief Set the value of the config entry
     *
     * No effect if the validator lambda returns false
     *
     * @param value
     */
    void set(T value);

    /**
     * @brief Set the entry to the default value
     *
     */
    void reset();

   private:
    string id;
    T defaultValue;
    T currentValue;

    /**
     * @brief The validator function is used to check if the value when setting
     * it.
     *
     * When the function returns false, the set is ignored and a warning is
     * issued. This allows to limit the values that each config entry can
     * receive (clamp it, between 0 and 1, etc.).
     *
     */
    function<bool(T)> validator;
};

template class ConfigEntry<string>;
template class ConfigEntry<unsigned int>;

#endif  // CONFIG_ENTRY_H