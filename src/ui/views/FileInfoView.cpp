/**
 * @file FileInfoView.hpp
 * @brief Declaration of the ui::FileInfoView class that provides functionality for the file information view.
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/FileInfoView.hpp"

namespace ui {

    /**
     * @brief Constructor for the FileInfoView class.
     * Initializes the manager and switch callback.
     * @param manager The NcursesManager instance to manage the UI.
     * @param switchCallback The callback function to switch views.
     */
    FileInfoView::FileInfoView(NcursesManager& manager, std::function<void(ViewType)> switchCallback)
        : _manager(manager), _switchCallback(switchCallback) {}

    /**
     * @brief Handles user input for the FileInfoView.
     * Processes the input character and performs actions based on it.
     * @param ch The input character.
     */
    void FileInfoView::handleInput(int ch) {
        if (ch == 'b') {
            _switchCallback(ViewType::MAIN_MENU);
        }
    }

    /**
     * @brief Updates the FileInfoView.
     * Clears the window, draws the text, and refreshes the UI.
     */
    void FileInfoView::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 1, 2, "[INFO FICHIER]");
        _manager.drawText(0, 3, 2, "Pas encore connecté à un fichier réel.");
        _manager.drawText(0, 5, 2, "Appuie sur 'b' pour revenir.");
        _manager.refreshAll();
    }

} // namespace ui
