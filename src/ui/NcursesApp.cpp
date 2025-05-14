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
        initLayout();
        switchView(ViewType::MAIN_MENU);
    }

    /**
     * @brief Destructor for the NcursesApp class.
     * Cleans up the ncurses library and any allocated resources.
     */
    NcursesApp::~NcursesApp() {
        _wrapper.end();
    }

    void NcursesApp::initLayout() {
        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX);

        // Dimensions dynamiques (ajustables selon goût)
        int sidebarWidth = maxX / 5;
        int infoHeight = 5;
        int statusHeight = 3;

        int explorerWidth = maxX - sidebarWidth;
        int explorerHeight = maxY - infoHeight - statusHeight;

        // Création et enregistrement des fenêtres
        _manager.createAndRegisterWindow(WindowRole::SIDEBAR, explorerHeight, sidebarWidth, 0, 0);
        _manager.createAndRegisterWindow(WindowRole::EXPLORER, explorerHeight, explorerWidth, 0, sidebarWidth);
        _manager.createAndRegisterWindow(WindowRole::INFO, infoHeight, maxX / 2, explorerHeight, 0);
        _manager.createAndRegisterWindow(WindowRole::STATUS, statusHeight, maxX / 2, explorerHeight + infoHeight, maxX / 2);
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
                _currentView = std::make_unique<SidebarView>(_manager, switchViewCallback);
                break;
            case ViewType::EXPLORER:
                _currentView = std::make_unique<ExplorerView>(_manager, *this, switchViewCallback);
                break;
            case ViewType::FILE_INFO:
                if (!_selectedFile) {
                    _currentView = std::make_unique<SidebarView>(_manager, switchViewCallback);
                    return;
                }
                _currentView = std::make_unique<FileInfoView>(_manager, *_selectedFile, switchViewCallback);
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
