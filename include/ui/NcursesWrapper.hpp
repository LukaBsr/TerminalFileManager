/**
 * @file NcursesWrapper.hpp
 * @brief Declaration of the ui::NcursesWrapper class that provides functionality for managing ncurses-based UI.
 */

#ifndef NCURSES_WRAPPER_HPP
    #define NCURSES_WRAPPER_HPP

    #include <ncurses.h>
    #include <string>

namespace ui {

    /**
     * @class NcursesWrapper
     * @brief A class that provides a wrapper around ncurses functions for terminal UI management.
     *
     * This class encapsulates the initialization, termination, and basic operations of the ncurses library.
     * It provides methods for creating and managing windows, printing text, and handling user input.
     */

    class NcursesWrapper {
    public:
        NcursesWrapper();
        ~NcursesWrapper();

        void init();
        void end();

        void refresh();
        void clear();
        void printText(int y, int x, const std::string& text);

        WINDOW* createWindow(int height, int width, int startY, int startX);
        void destroyWindow(WINDOW* window);
        void clearWindow(WINDOW* window);
        void refreshWindow(WINDOW* window);
        void drawTextInWindow(WINDOW* window, int y, int x, const std::string& text);

        int getChar();
    
    protected:
    private:
    };

} // namespace ui

#endif // NCURSES_WRAPPER_HPP