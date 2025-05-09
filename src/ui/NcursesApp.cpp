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
     * Initializes the ncurses library and creates the main window.
     */
    NcursesApp::NcursesApp() : _manager(_wrapper), _running(true) {
        _wrapper.init();
        _manager.createWindow(20, 60, 1, 2);
        switchView(ViewType::MAIN_MENU);
    }

    /**
     * @brief Destructor for the NcursesApp class.
     * Cleans up the ncurses library and any allocated resources.
     */
    NcursesApp::~NcursesApp() {
        _wrapper.end();
    }

    /**
     * @brief Runs the main application loop.
     * Continuously updates the UI and handles user input until the application is terminated.
     */
    void NcursesApp::run() {
        while (_running) {
            update();
            handleUserInput();
        }
    }

    /**
     * @brief Switches the current view to the specified view type.
     * @param type The type of view to switch to.
     */
    void NcursesApp::switchView(ViewType type) {
        switch (type) {
            case ViewType::MAIN_MENU:
                _currentView = std::make_unique<MainMenuView>(_manager, [this](ViewType next) {
                    this->switchView(next);
                });
                break;
            case ViewType::EXPLORER:
                _currentView = std::make_unique<ExplorerView>(_manager, [this](ViewType next) {
                    this->switchView(next);
                });
                break;
            case ViewType::FILE_INFO:
                _currentView = std::make_unique<FileInfoView>(_manager, [this](ViewType next) {
                    this->switchView(next);
                });
                break;
            case ViewType::QUIT:
                _running = false;
                break;
        }
    }

    /**
     * @brief Handles user input and passes it to the current view.
     */
    void NcursesApp::handleUserInput() {
        int ch = _wrapper.getChar();
        if (_currentView)
            _currentView->handleInput(ch);
    }

    /**
     * @brief Updates the current view.
     * Calls the update method of the current view to refresh the UI.
     */
    void NcursesApp::update() {
        if (_currentView)
            _currentView->update();
    }

} // namespace ui
