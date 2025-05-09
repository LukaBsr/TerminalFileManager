/**
 * @file NcursesManager.hpp
 * @brief Declaration of the ui::NcursesManager class that provides functionality for managing ncurses-based UI components.
 */

#ifndef NCURSES_MANAGER_HPP
    #define NCURSES_MANAGER_HPP

    #include "NcursesWrapper.hpp"

    #include <vector>

namespace ui {

    /**
     * @class NcursesManager
     * @brief A class that manages ncurses-based UI components.
     *
     * This class provides methods for initializing and terminating the ncurses library,
     * creating and destroying windows, drawing borders, updating windows, printing text,
     * clearing windows, and refreshing the screen.
     */

    class NcursesManager {
    public:
        NcursesManager(NcursesWrapper& wrapper);
        ~NcursesManager();
    
        int createWindow(int height, int width, int startY, int startX);
        void drawText(int winIndex, int y, int x, const std::string& text);
        void clearWindow(int winIndex);
        void refreshAll();
    
    private:
        NcursesWrapper& _wrapper;
        std::vector<WINDOW*> _windows;
    };
    
} // namespace ui

#endif // NCURSES_MANAGER_HPP
