/**
 * @file FileInfoView.cpp
 * @brief Declaration of the ui::FileInfoView class that provides functionality for the file information view.
 * @author [Boissiere Luka]
 * @date 2025-05-09
 */

#include "ui/views/FileInfoView.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>

namespace ui {

    std::string getLocalizedString(const std::string& key);

    /**
     * @brief Constructor for the FileInfoView class.
     * Initializes the file information view with the given file and switch callback.
     * @param manager The NcursesManager instance to manage the UI.
     * @param file The file to display information about.
     * @param switchCallback The callback function to switch views.
     */
    FileInfoView::FileInfoView(NcursesManager& manager, const core::File& file, std::function<void(ViewType)> switchCallback)
        : _manager(manager), _switchCallback(switchCallback), _file(file)
    {}

    /**
     * @brief Handles user input for the FileInfoView.
     * Processes the input character and performs actions based on it.
     * @param ch The input character.
     */
    void FileInfoView::handleInput(int ch) {
        if (ch == 'q' || ch == '\n' || ch == 10) {
            _switchCallback(ViewType::MAIN_MENU);
        }
    }

    /**
     * @brief Updates the FileInfoView.
     * Clears the window, draws the text, and refreshes the UI.
     */
    void FileInfoView::update() {
        WINDOW* win = _manager.getWindow(WindowRole::SIDEBAR);
        auto& wrapper = _manager.getWrapper();
    
        wrapper.clearWindow(win);
        box(win, 0, 0);
        wrapper.drawTextInWindow(win, 0, 2, " Informations ");
    
        int max_y, max_x;
        getmaxyx(win, max_y, max_x);
    
        wrapper.drawTextInWindow(win, 2, 2, "Nom: " + _file.getName());
        wrapper.drawTextInWindow(win, 3, 2, "Chemin: " + _file.getPath());
        wrapper.drawTextInWindow(win, 4, 2, "Type: " + std::string(_file.isDirectory() ? "Dossier" : "Fichier"));
        wrapper.drawTextInWindow(win, 5, 2, "Taille: " + formatSize(_file.getSize()));
        wrapper.drawTextInWindow(win, 6, 2, "Modifié: " + formatTime(_file.getLastModified()));
    
        wrapper.drawTextInWindow(win, max_y - 2, 2, "[Entrée] ou [q] pour retourner");
    
        wrapper.refreshWindow(win);
    }

    /**
     * @brief Formats the file size into a human-readable string.
     * @param size The file size in bytes.
     * @return A formatted string representing the file size.
     */
    std::string FileInfoView::formatSize(std::uintmax_t size) const {
        std::ostringstream oss;
        if (size >= 1'000'000)
            oss << (size / 1'000'000) << " " << getLocalizedString("megabytes");
        else if (size >= 1'000)
            oss << (size / 1'000.0) << " Ko";
        else
            oss << size << " o";
        return oss.str();
    }

    /**
     * @brief Formats the time into a human-readable string.
     * @param time The time in seconds since the epoch.
     * @return A formatted string representing the time.
     */
    std::string FileInfoView::formatTime(std::time_t time) const {
        std::ostringstream oss;
        std::tm* tm = std::localtime(&time);
        if (tm != nullptr) {
            oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        } else {
            oss << "Invalid time";
        }
        return oss.str();
    }

    /**
     * @brief Retrieves a localized string based on the provided key.
     * @param key The key for the localized string.
     * @return The localized string.
     */
    std::string getLocalizedString(const std::string& key) {
        // Example localization map (replace with actual implementation)
        static const std::unordered_map<std::string, std::string> localizationMap = {
            {"file_selected", "Fichier sélectionné"},
            {"megabytes", "MB"},
            {"kilobytes", "KB"},
            {"bytes", "B"}
        };

        auto it = localizationMap.find(key);
        return it != localizationMap.end() ? it->second : key;
    }

} // namespace ui
