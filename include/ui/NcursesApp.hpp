/**
 * @file NcursesApp.hpp
 * @brief Declaration of the ui::NcursesApp class that provides functionality for managing the main application loop and user interactions.
 */

#ifndef NCURSESAPP_HPP
    #define NCURSESAPP_HPP

    #include "NcursesManager.hpp"
    #include <functional>

namespace ui {

    /**
     * @struct MenuOption
     * @brief A structure that represents a menu option with a label and an action.
     *
     * This structure is used to define the options available in the menu, including
     * the label to be displayed and the action to be executed when the option is selected.
     */
    
    struct MenuOption {
        std::string label;
        std::function<void()> action;
    };

    /**
     * @class NcursesApp
     * @brief A class that manages the main application loop and user interactions.
     *
     * This class provides methods for running the application, handling user input,
     * updating the UI, and managing the ncurses library.
     */

    class NcursesApp {
    public:
        NcursesApp();
        ~NcursesApp();

        void run();

    private:
        NcursesWrapper _wrapper;
        NcursesManager _manager;

        std::vector<MenuOption> _menuOptions;
        int _selectedIndex;
        bool _running;
    
        int _titleWin;
        int _menuWin;
        int _contentWin;

        void handleUserInput();
        void update();
    };

} // namespace ui

#endif
