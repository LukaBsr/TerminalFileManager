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

    void ExplorerView::createNewFile() {
        NcursesWrapper& wrapper = _manager.getWrapper();
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
    
        int popup_h = 3;
        int popup_w = 50;
        int popup_y = (max_y - popup_h) - 1;
        int popup_x = 2;
    
        WINDOW* inputWin = wrapper.createWindow(popup_h, popup_w, popup_y, popup_x);
        box(inputWin, 0, 0);
        wrapper.drawTextInWindow(inputWin, 1, 2, "Nom du fichier: ");
        wrapper.refreshWindow(inputWin);
    
        char filename[256];
        echo();
        wgetnstr(inputWin, filename, 255);
        noecho();
    
        wrapper.destroyWindow(inputWin);
    
        std::string fullPath = _directory.getPath() + "/" + filename;
        if (std::filesystem::exists(fullPath)) {
            wrapper.drawTextInWindow(_manager.getWindow(WindowRole::EXPLORER), 0, 0, "Fichier déjà existant !");
            return;
        }
    
        std::ofstream newFile(fullPath);
        if (newFile) {
            newFile.close();
            wrapper.drawTextInWindow(_manager.getWindow(WindowRole::EXPLORER), 0, 0, "Fichier créé avec succès !");
            _fileNames = _directory.listFiles();
        } else {
            wrapper.drawTextInWindow(_manager.getWindow(WindowRole::EXPLORER), 0, 0, "Erreur: création échouée");
        }
    
        _switchCallback(ViewType::EXPLORER);
    }    

    void ExplorerView::createNewDirectory() {
        NcursesWrapper& wrapper = _manager.getWrapper();
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
    
        int popup_h = 3;
        int popup_w = 50;
        int popup_y = (max_y - popup_h) - 1;
        int popup_x = 2;
    
        WINDOW* inputWin = wrapper.createWindow(popup_h, popup_w, popup_y, popup_x);
        box(inputWin, 0, 0);
        wrapper.drawTextInWindow(inputWin, 1, 2, "Nom du dossier: ");
        wrapper.refreshWindow(inputWin);
    
        char dirname[256];
        echo();
        wgetnstr(inputWin, dirname, 255);
        noecho();
    
        wrapper.destroyWindow(inputWin);
    
        std::string fullPath = _directory.getPath() + "/" + dirname;
        if (std::filesystem::exists(fullPath)) {
            wrapper.drawTextInWindow(_manager.getWindow(WindowRole::EXPLORER), 0, 0, "Dossier déjà existant !");
            return;
        }
    
        if (std::filesystem::create_directory(fullPath)) {
            _fileNames = _directory.listFiles();
        } else {
            wrapper.drawTextInWindow(_manager.getWindow(WindowRole::EXPLORER), 0, 0, "Erreur: création échouée");
        }
    
        _switchCallback(ViewType::EXPLORER);
    }    

    void ExplorerView::deleteSelected() {
        if (_fileNames.empty()) return;
    
        std::string name = _fileNames[_selectedIndex];
        std::string fullPath = _directory.getPath() + "/" + name;
    
        NcursesWrapper& wrapper = _manager.getWrapper();
    
        try {
            std::filesystem::directory_entry entry(fullPath);
            if (entry.is_directory()) {
                std::filesystem::remove_all(fullPath);
            } else {
                std::filesystem::remove(fullPath);
            }
    
            _fileNames = _directory.listFiles();
            if (_selectedIndex >= static_cast<int>(_fileNames.size())) {
                _selectedIndex = std::max(0, static_cast<int>(_fileNames.size()) - 1);
            }
    
            _switchCallback(ViewType::EXPLORER);
        } catch (const std::exception& e) {
            wrapper.drawTextInWindow(_manager.getWindow(WindowRole::EXPLORER), 0, 0, "Erreur: suppression échouée");
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
                createNewFile();
                break;
            case 'd':
                createNewDirectory();
                break;
            case 'x':
                deleteSelected();
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
            std::string display = (_selectedIndex == static_cast<int>(i) ? "> " : "  ") + _fileNames[i];
            if (_selectedIndex == static_cast<int>(i)) wattron(win, A_REVERSE);
            wrapper.drawTextInWindow(win, 3 + i, 2, display);
            if (_selectedIndex == static_cast<int>(i)) wattroff(win, A_REVERSE);
        }

        int max_y, max_x;
        getmaxyx(win, max_y, max_x);
        wrapper.drawTextInWindow(win, max_y - 3, 2, "[Entrée] Ouvrir  [q] Menu");
        wrapper.drawTextInWindow(win, max_y - 2, 2, "[n] Nouveau  [d] Dossier  [x] Supprimer");

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
