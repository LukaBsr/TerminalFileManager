/**
 * @file ExplorerView.hpp
 * @brief Declaration of the ui::ExplorerView class that provides functionality for the explorer view.
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/ExplorerView.hpp"

namespace ui {

    /**
     * @brief Constructor for the ExplorerView class.
     * Initializes the manager and switch callback.
     * @param manager The NcursesManager instance to manage the UI.
     * @param switchCallback The callback function to switch views.
     */
    ExplorerView::ExplorerView(NcursesManager& manager, std::function<void(ViewType)> switchCallback)
        : _manager(manager), _switchCallback(switchCallback) {}

    /**
     * @brief Handles user input for the ExplorerView.
     * Processes the input character and performs actions based on it.
     * @param ch The input character.
     */
    void ExplorerView::handleInput(int ch) {
        if (ch == 'b') {
            _switchCallback(ViewType::MAIN_MENU);
        }
    }

    /**
     * @brief Updates the ExplorerView.
     * Clears the window, draws the text, and refreshes the UI.
     */
    void ExplorerView::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 1, 2, "[EXPLORER]");
        _manager.drawText(0, 3, 2, "Contenu fictif à explorer...");
        _manager.drawText(0, 5, 2, "Appuie sur 'b' pour revenir.");
        _manager.refreshAll();
    }

} // namespace ui
