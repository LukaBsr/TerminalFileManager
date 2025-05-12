/**
 * @file ExplorerView.hpp
 * @brief Declaration of the ui::ExplorerView class that provides functionality for the explorer view.
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/ExplorerView.hpp"
#include "ui/NcursesApp.hpp"
#include <memory>

namespace ui {

    /**
     * @brief Constructor for the ExplorerView class.
     * Initializes the directory, file names, selected index, and switch callback.
     * @param manager The NcursesManager instance to manage the UI.
     * @param switchCallback The callback function to switch views.
     */
    ExplorerView::ExplorerView(NcursesManager& manager, NcursesApp& parent, std::function<void(ViewType)> switchCallback)
        : _directory("."), _selectedIndex(0), _manager(manager), _parent(parent), _switchCallback(switchCallback)
    {
        try {
            _fileNames = _directory.listFiles();
        } catch (const std::exception& e) {
            _fileNames.clear();
            _manager.drawText(0, 0, 2, "Error: Unable to list files in the directory.");
        }
    }

    /**
     * @brief Handles user input for the ExplorerView.
     * Processes the input character and performs actions based on it.
     * @param ch The input character.
     */
    void ExplorerView::handleInput(int ch) {
        switch (ch) {
            case KEY_UP:
                _selectedIndex = (_selectedIndex - 1 + _fileNames.size()) % _fileNames.size();
                break;
            case KEY_DOWN:
                _selectedIndex = (_selectedIndex + 1) % _fileNames.size();
                break;
            case '\n':
            case KEY_ENTER:
                enterSelected();
                break;
            case 'q':
                _switchCallback(ViewType::MAIN_MENU);
                break;
        }
    }

    /**
     * @brief Updates the ExplorerView.
     * Clears the window, draws the text, and refreshes the UI.
     */
    void ExplorerView::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 0, 2, "Explorateur de fichiers");
        _manager.drawText(0, 1, 2, "========================");

        for (std::size_t i = 0; i < _fileNames.size(); ++i) {
            std::string display = (_selectedIndex == static_cast<int>(i) ? "> " : "  ") + _fileNames[i];
            _manager.drawText(0, 3 + i, 2, display);
        }

        _manager.refreshAll();
    }

    /**
     * @brief Enters the selected file or directory.
     * If the selected item is a directory, it updates the current directory and lists its files.
     * If it's a file, it switches to the file information view.
     */
    void ExplorerView::enterSelected() {
        const std::string& selectedName = _fileNames[_selectedIndex];
        std::string newPath = _directory.getPath() + "/" + selectedName;

        std::filesystem::directory_entry entry(newPath);
        if (entry.is_directory()) {
            _directory.setPath(newPath);
            _fileNames = _directory.listFiles();
            _selectedIndex = 0;
        } else {
            auto file = std::make_shared<core::File>(entry);
            _parent.setSelectedFile(file);
            _switchCallback(ViewType::FILE_INFO);
        }
    }

} // namespace ui
