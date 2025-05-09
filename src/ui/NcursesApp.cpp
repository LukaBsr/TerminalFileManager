/**
 * @file NcursesApp.cpp
 * @brief Implementation of the ui::NcursesApp class
 * @author [Boissiere Luka]
 * @date 2025-05-07
 */

#include "ui/NcursesApp.hpp"

namespace ui {

    /**
     * @brief Constructor for the NcursesApp class.
     * Initializes the ncurses wrapper, creates a window, and sets up menu options.
     */

     NcursesApp::NcursesApp() : _manager(_wrapper), _selectedIndex(0), _running(true) {
        _wrapper.init();
        _manager.createWindow(10, 40, 2, 4);
    
        _menuOptions = {
            { "Afficher message", [this]() { 
                _manager.drawText(0, 8, 1, "Tu as choisi l'option 1!");
            }},
            { "Changer fenêtre", [this]() {
                _manager.createWindow(6, 20, 5, 50);
            }},
            { "Quitter", [this]() {
                _running = false;
            }}
        };
    }
    

    NcursesApp::~NcursesApp() {
        _wrapper.end();
    }

    void NcursesApp::run() {
        while (_running) {
            update();
            handleUserInput();
        }
    }

    /**
     * @brief Handles user input for navigation and quitting the application.
     * Uses arrow keys for navigation and 'q' or Enter to quit.
     */

    void NcursesApp::handleUserInput() {
        int ch = _wrapper.getChar();
    
        switch (ch) {
            case KEY_UP:
                _selectedIndex = (_selectedIndex - 1 + _menuOptions.size()) % _menuOptions.size();
                break;
            case KEY_DOWN:
                _selectedIndex = (_selectedIndex + 1) % _menuOptions.size();
                break;
            case '\n':
            case KEY_ENTER:
                if (_selectedIndex >= 0 && _selectedIndex < static_cast<int>(_menuOptions.size()))
                    _menuOptions[_selectedIndex].action();
                break;
        }
    }    

    /**
     * @brief Updates the UI by clearing and redrawing the windows.
     * Draws the title, menu options, and content based on the selected index.
     */

     void NcursesApp::update() {
        _manager.clearWindow(0);

        _manager.drawText(0, 0, 2, "Terminal File Manager");
        _manager.drawText(0, 1, 2, "========================");
        for (std::size_t i = 0; i < _menuOptions.size(); ++i) {
            std::string text = (_selectedIndex == static_cast<int>(i) ? "> " : "  ") + _menuOptions[i].label;
            _manager.drawText(0, 4 + i, 2, text);
        }
        _manager.refreshAll();
    }
    

} // namespace ui
