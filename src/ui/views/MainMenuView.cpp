/**
 * @file MainMenuView.cpp
 * @brief Implementation of the ui::MainMenuView class
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/MainMenuView.hpp"

namespace ui {

    MainMenuView::MainMenuView(NcursesManager& manager, std::function<void(ViewType)> switchCallback)
        : _manager(manager), _switchCallback(switchCallback), _selectedIndex(0) {
        _options = { "Explorer", "Afficher Info Fichier", "Quitter" };
    }

    void MainMenuView::handleInput(int ch) {
        switch (ch) {
            case KEY_UP:
                _selectedIndex = (_selectedIndex - 1 + _options.size()) % _options.size();
                break;
            case KEY_DOWN:
                _selectedIndex = (_selectedIndex + 1) % _options.size();
                break;
            case '\n':
            case KEY_ENTER:
                switch (_selectedIndex) {
                    case 0:
                        _switchCallback(ViewType::EXPLORER);
                        break;
                    case 1:
                        _switchCallback(ViewType::FILE_INFO);
                        break;
                    case 2:
                        _switchCallback(ViewType::QUIT);
                        break;
                }
                break;
        }
    }

    void MainMenuView::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 1, 2, "[MENU PRINCIPAL]");
        for (std::size_t i = 0; i < _options.size(); ++i) {
            std::string label = (_selectedIndex == static_cast<int>(i) ? "> " : "  ") + _options[i];
            _manager.drawText(0, 3 + i, 2, label);
        }
        _manager.refreshAll();
    }

} // namespace ui
