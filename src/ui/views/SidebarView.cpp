/**
 * @file MainMenuView.cpp
 * @brief Implementation of the ui::MainMenuView class
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/SidebarView.hpp"

namespace ui {

    SidebarView::SidebarView(NcursesManager& manager, std::function<void(ViewType)> onSwitch)
        : _manager(manager), _onSwitch(std::move(onSwitch)) {}

    void SidebarView::update() {
        _manager.clearWindow(static_cast<int>(WindowRole::SIDEBAR));
        drawMenu();
        _manager.refreshAll();
    }

    void SidebarView::handleInput(int ch) {
        switch (ch) {
            case KEY_UP:
                if (_selectedIndex > 0) _selectedIndex--;
                break;
            case KEY_DOWN:
                if (_selectedIndex + 1 < _options.size()) _selectedIndex++;
                break;
            case '\n':
                if (_options[_selectedIndex] == "Explorer") {
                    _onSwitch(ViewType::EXPLORER);
                } else if (_options[_selectedIndex] == "Quitter") {
                    _onSwitch(ViewType::QUIT);
                }
                break;
        }
    }

    void SidebarView::drawMenu() {
        WINDOW* win = _manager.getWindow(WindowRole::SIDEBAR);
        box(win, 0, 0);
        mvwprintw(win, 0, 2, " Menu ");

        for (size_t i = 0; i < _options.size(); ++i) {
            if (i == _selectedIndex)
                wattron(win, A_REVERSE);
            mvwprintw(win, 2 + i, 2, "%s", _options[i].c_str());
            if (i == _selectedIndex)
                wattroff(win, A_REVERSE);
        }
    }

} // namespace ui
