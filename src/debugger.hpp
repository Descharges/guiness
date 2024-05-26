#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <ncurses.h>

#define HEADER_PAIR 1
#define WARN_PAIR 2
#define ERR_PAIR 3
#define DEFAULT_PAIR 4
#define INFO_PAIR 5
#define MIN_LOG_HEIGHT 10
#define MIN_LOG_WIDTH 68
#define LOG_TOP_OFFSET 2
#define SYSTEM_STATUS_HEIGHT 5
#define RAM_BROWSER_WIDTH 34

/**
 * @brief Class responsible for the debug interface.
 *
 * Creates, destroys and handles the content of the
 * Ncurses windows
 *
 */
class Debugger {
   public:
    /**
     * @brief Construct a new Debugger object.
     *
     * Initialize NCurses and all the windows used
     * in the CLI.
     *
     */
    Debugger();

    /**
     * @brief Destroy the Debugger object.
     *
     * Destroys windows and terminates the Ncurses
     * Context
     *
     */
    ~Debugger();

    /**
     * @brief Displays text in the log window of the interface
     *
     * @param p_message The text to be displayed
     */
    void displayLogMessage(const char *p_message);

    /**
     * @brief Refresh all of the Ncurses windows
     *
     */
    void updateWindows();

    /**
     * @brief Get the Log Window object
     *
     * @return WINDOW* Pointer to the log window
     */
    WINDOW *getLogWindow();

   private:
    /** The main window, containing all of the other windows*/
    WINDOW *p_mainWin;

    /** The window displaying log messages*/
    WINDOW *p_logWin;

    /** The windows displaying the status of the emulated system*/
    WINDOW *p_stateWin;

    /** The ram browser window*/
    WINDOW *p_ramWin;

    /**
     * @brief Forces the user to resize terminal.
     * Will return the main Ncurses window when
     * the terminal is big enough to display the
     * entierity of the debugger.
     *
     * @return WINDOW*
     */
    WINDOW *getLargeWindow();

    /**
     * @brief Check if color display is available, throws an error if not.
     *
     * @param p_mainWindow The main Ncurses window.
     */
    void checkColorDisponibility(WINDOW *p_mainWindow);

    /**
     * @brief Initialize the different color pairs used in the debugger
     *
     */
    void initColors();

    /**
     * @brief Writes the header in the main window
     *
     */
    void initHeader();

    /**
     * @brief Initialize all the windows used in the debugger
     *
     * @param p_mainWindow The main window
     * @param ram_width The expected width of the ram browser window
     * @param cpu_height The expected height of the status section window
     * @param log_top_offset The expected height of the header
     */
    void initWindows(WINDOW *p_mainWindow, int ram_width, int status_height,
                     int log_top_offset);
};

#endif