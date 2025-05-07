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
        _manager.createWindow(10, 40, 2, 4);
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

    void NcursesApp::handleUserInput() {
        int ch = _wrapper.getChar();
        if (ch == 'q') {
            _running = false;
        }
    }

    void NcursesApp::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 1, 1, "App en cours... Appuie sur 'q' pour quitter.");
        _manager.refreshAll();
    }

} // namespace ui
