/**
 * @file NcursesApp.cpp
 * @brief Implementation of the ui::NcursesApp class
 * @author [Boissiere Luka]
 * @date 2025-05-07
 */

#include "ui/NcursesApp.hpp"

namespace ui {

    NcursesApp::NcursesApp() : _manager(_wrapper), _running(true) {
        _wrapper.init();
        _manager.createWindow(20, 60, 1, 2);
        switchView(ViewType::MAIN_MENU);
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

    void NcursesApp::handleUserInput() {
        int ch = _wrapper.getChar();
        if (_currentView)
            _currentView->handleInput(ch);
    }

    void NcursesApp::update() {
        if (_currentView)
            _currentView->update();
    }

} // namespace ui
