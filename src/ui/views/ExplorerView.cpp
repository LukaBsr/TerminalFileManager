/**
 * @file ExplorerView.hpp
 * @brief Declaration of the ui::ExplorerView class that provides functionality for the explorer view.
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/ExplorerView.hpp"
#include "ui/NcursesApp.hpp"
#include <memory>
#include <fstream>
#include <ncurses.h>

namespace ui {

    /**
     * @brief Constructor for the ExplorerView class.
     * Initializes the explorer view with the given manager, parent application, and switch callback.
     * @param manager The NcursesManager instance to manage the UI.
     * @param parent The parent application instance.
     * @param switchCallback The callback function to switch views.
     */
    ExplorerView::ExplorerView(NcursesManager& manager, NcursesApp& parent, std::function<void(ViewType)> switchCallback)
        : _directory("."), _selectedIndex(0), _manager(manager), _parent(parent), _switchCallback(switchCallback)
    {
        try {
            _context = std::make_unique<ExplorerContext>(ExplorerContext {
                _manager,
                _parent,
                _directory,
                _fileNames,
                _selectedIndex,
                _switchCallback,
                _copiedPath
            });
            _actionHandler = std::make_unique<FileActionHandler>(*_context);
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
            case 'n':
                _actionHandler->createNewFile();
                break;
            case 'd':
                _actionHandler->createNewDirectory();
                break;
            case 'x':
                _actionHandler->deleteSelected();
                break;
                case 'z':
                _actionHandler->zipSelected();
                break;
            case 'u':
                _actionHandler->unzipSelected();
                break;
            case 'b':
                _actionHandler->goBackToParent();
                break;
            case 'r':
                _actionHandler->renameSelected();
                break;
            case 'c':
                _actionHandler->copySelected();
                break;
            case 'v':
                _actionHandler->pasteCopied();
                break;            
        }
    }

    /**
     * @brief Updates the ExplorerView.
     * Clears the window, draws the text, and refreshes the UI.
     */
    void ExplorerView::update() {
        WINDOW* win = _manager.getWindow(WindowRole::EXPLORER);
        NcursesWrapper& wrapper = _manager.getWrapper();
    
        wrapper.clearWindow(win);
        box(win, 0, 0);
        wrapper.drawTextInWindow(win, 0, 2, " Explorateur ");
    
        wrapper.drawTextInWindow(win, 1, 2, "Dossier courant: " + _directory.getPath());
    
        for (std::size_t i = 0; i < _fileNames.size(); ++i) {
            std::string name = _fileNames[i];
            std::string fullPath = _directory.getPath() + "/" + name;
    
            int colorPair = 2;
    
            try {
                std::filesystem::directory_entry entry(fullPath);
                if (entry.is_directory()) {
                    colorPair = 1;
                } else if ((entry.status().permissions() & std::filesystem::perms::owner_exec) != std::filesystem::perms::none) {
                    colorPair = 3;
                } else if (entry.is_symlink()) {
                    colorPair = 4;
                } else if (_actionHandler->isArchive(name)) {
                    colorPair = 5;
                }
            } catch (...) {
                colorPair = 2;
            }
    
            if (_selectedIndex == static_cast<int>(i)) wattron(win, A_REVERSE);
            wattron(win, COLOR_PAIR(colorPair));
            wrapper.drawTextInWindow(win, 3 + i, 2, (_selectedIndex == static_cast<int>(i) ? "> " : "  ") + name);
            wattroff(win, COLOR_PAIR(colorPair));
            if (_selectedIndex == static_cast<int>(i)) wattroff(win, A_REVERSE);
        }
    
        int max_y, max_x;
        getmaxyx(win, max_y, max_x);

        wrapper.drawTextInWindow(win, max_y - 3, 2, "[Entrée] Ouvrir  [q] Menu");

        std::string rightLine1 = "[x] Supprimer  [b] Retour  [r] Renommer";
        int right1_x = max_x - static_cast<int>(rightLine1.length()) - 2;
        wrapper.drawTextInWindow(win, max_y - 3, right1_x, rightLine1);

        wrapper.drawTextInWindow(win, max_y - 2, 2, "[n] Nouveau fichier  [d] Nouveau dossier");
        std::string rightLine2 = "[z] Zip  [u] Unzip [c] Copier  [v] Coller";
        int right2_x = max_x - static_cast<int>(rightLine2.length()) - 2;
        wrapper.drawTextInWindow(win, max_y - 2, right2_x, rightLine2);
    
        wrapper.refreshWindow(win);
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
