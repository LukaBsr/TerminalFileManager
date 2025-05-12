/**
 * @file NcursesApp.cpp
 * @brief Implementation of the ui::NcursesApp class
 * @author [Boissiere Luka]
 * @date 2025-05-07
 */

#include "ui/NcursesApp.hpp"
#include <mutex>

namespace ui {

#include <mutex>

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
        auto switchViewCallback = [this](ViewType next) {
            this->switchView(next);
        };

        switch (type) {
            case ViewType::MAIN_MENU:
                _currentView = std::make_unique<MainMenuView>(_manager, switchViewCallback);
                break;
            case ViewType::EXPLORER:
                _currentView = std::make_unique<ExplorerView>(_manager, *this, switchViewCallback);
                break;
            case ViewType::FILE_INFO: {
                const auto& file = _selectedFile;
                if (!file) {
                    _currentView = std::make_unique<MainMenuView>(_manager, switchViewCallback);
                    return;
                }
                _currentView = std::make_unique<FileInfoView>(_manager, *file, switchViewCallback);
                break;
            }
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

    /**
     * @brief Sets the selected file.
     * Transfers ownership of the provided file to the `_selectedFile` member.
     * @param file The file to be set as selected.
     */
    void NcursesApp::setSelectedFile(std::shared_ptr<core::File> file) {
        std::lock_guard<std::mutex> lock(_fileMutex);
        _selectedFile = std::move(file);
    } 

} // namespace ui
