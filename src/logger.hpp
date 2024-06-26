#ifndef LOGGER_H
#define LOGGER_H

#include <ncurses.h>

#include <cstdint>
#include <sstream>
#include <string>

#define HEADER_PAIR 1
#define WARN_PAIR 2
#define ERR_PAIR 3
#define DEFAULT_PAIR 4
#define INFO_PAIR 5

using std::string;
using std::stringstream;


enum LogLevel { debug, info, warning, error };

class IdLogger;

/**
 * @brief Singelton used for logging
 *
 */
class Logger {
   public:
    /**
     * @brief create a new Logger Proxy object
     * This is the object with which is used to log messages
     *
     * @param p_id the string identifier which will be reported in the logs when
     * using the proxy
     * @return IdLogger the newly created proxy
     */
    static IdLogger newIdLogger(const char *p_id);

    /**
     * @brief Format 8 bit numbers as hexadecimal in a string (255 -> 0xFF)
     *
     * @param n The 8 bit number to format
     * @return string The formated string
     */
    static string formatHex8(uint8_t n);

    /**
     * @brief Format 16 bit numbers as hexadecimal in a string (65536 -> 0xFFFF)
     *
     * @param n The 16 bit number to format
     * @return string The formated string
     */
    static string formatHex16(uint16_t n);

    /**
     * @brief Set the Ncurses window which will receive log messages
     *
     * @param p_targetWindow Ncurses window
     */
    void setPrintTarget(WINDOW *p_targetWindow);

    /**
     * @brief Print log message to target windows if set, STDOUT if not
     *
     * @param p_id The string identifier of the message
     * @param p_message The log message
     * @param lvl The log level
     */
    void printLogMessage(const char *p_id, const char *p_message, LogLevel lvl);

   private:
    /**
     * @brief Construct a new Logger object
     *
     */
    Logger();

    /**
     * @brief The singleton instance of Logger
     */
    static Logger s_instance;

    /**
     * @brief Ncurses windows which will receive log messages
     */
    WINDOW *p_displayWindow = NULL;
};

/**
 * @brief used to interract with the logger instance.
 * Forces to use a unique and constant identifier.
 */
class IdLogger {
   public:
    /**
     * @brief Logs a C string
     *
     * @param p_logMessage
     * @param lvl Log level
     */
    void logCStr(const char *p_logMessage, LogLevel lvl = debug);

    /**
     * @brief Logs a string
     *
     * @param logMessage
     * @param lvl  Log Level
     */
    void logStr(string logMessage, LogLevel lvl = debug);

    /**
     * @brief Logs a stringstream
     *
     * @param logStream
     * @param lvl Log level
     */
    void logSStream(stringstream &logStream, LogLevel lvl = debug);

    /**
     * @brief Construct a new Logger Proxy object
     * Using this constructor direclty is impossible since
     * obtaining a LoggerInstance is impossible.
     * The logger has a method to obtain a new IdLogger.
     *
     * @param p_id The string identifier
     * @param loggerInstance
     */
    IdLogger(const char *p_id, Logger &loggerInstance);

    /**
     * @brief Set the Ncurses window which will receive log messages
     *
     * @param p_targetWindow Ncurses window
     */
    void setPrintTarget(WINDOW *p_targetWindow);

    /**
     * @brief Get the String Stream object
     *
     * @return stringstream
     */
    stringstream &getStringStream();

    /**
     * @brief Display the content of the string stream and clears it.
     *
     */
    void flushSsLog(LogLevel lvl = debug);

    /**
     * @brief Adds a C string to the logger string stream.
     *
     * @param p_cStr The C string to add to the stream
     * @return IdLogger& Reference to itself
     */
    IdLogger &operator<<(const char *p_cStr);

    /**
     * @brief Adds a string to the logger string stream.
     *
     * @param str The string to add to the stream
     * @return IdLogger& Reference to itself
     */
    IdLogger &operator<<(string str);

   private:
    /** String identifier*/
    const char *p_id;

    /** Logger instance*/
    Logger &logger;

    /** String stream*/
    stringstream sslog;

    IdLogger();
};

#endif