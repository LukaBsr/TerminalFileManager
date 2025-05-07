/**
 * @file NcursesApp.hpp
 * @brief Declaration of the ui::NcursesApp class that provides functionality for managing the main application loop and user interactions.
 */

#ifndef NCURSESAPP_HPP
    #define NCURSESAPP_HPP

    #include "NcursesManager.hpp"

namespace ui {

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

        bool _running;

        void handleUserInput();
        void update();
    };

} // namespace ui

#endif
