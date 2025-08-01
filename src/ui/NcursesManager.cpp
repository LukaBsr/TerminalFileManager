/**
 * @file NcursesManager.cpp
 * @brief Implementation of the ui::NcursesManager class
 * @author [Boissiere Luka]
 * @date 2025-05-07
 */

#include "ui/NcursesManager.hpp"

namespace ui {

    NcursesManager::NcursesManager(NcursesWrapper& wrapper) : _wrapper(wrapper) {}

    NcursesManager::~NcursesManager() {
        for (auto win : _windows)
            _wrapper.destroyWindow(win);
    }

    int NcursesManager::createWindow(int height, int width, int startY, int startX) {
        _windows.push_back(_wrapper.createWindow(height, width, startY, startX));
        return static_cast<int>(_windows.size()) - 1;
    }    

    void NcursesManager::drawText(int winIndex, int y, int x, const std::string& text) {
        if (winIndex >= 0 && winIndex < static_cast<int>(_windows.size()))
            _wrapper.drawTextInWindow(_windows[winIndex], y, x, text);
    }

    void NcursesManager::clearWindow(int winIndex) {
        if (winIndex >= 0 && winIndex < static_cast<int>(_windows.size()))
            _wrapper.clearWindow(_windows[winIndex]);
    }

    void NcursesManager::refreshAll() {
        for (auto win : _windows)
            _wrapper.refreshWindow(win);
    }

    void NcursesManager::registerWindow(WindowRole role, WINDOW* window) {
        _roleMap[role] = window;
    }

    WINDOW* NcursesManager::getWindow(WindowRole role) {
        auto it = _roleMap.find(role);
        return (it != _roleMap.end()) ? it->second : nullptr;
    }
    
    WINDOW* NcursesManager::createAndRegisterWindow(WindowRole role, int height, int width, int startY, int startX) {
        WINDOW* window = _wrapper.createWindow(height, width, startY, startX);
        registerWindow(role, window);
        _windows.push_back(window);
        return window;
    }

} // namespace ui
