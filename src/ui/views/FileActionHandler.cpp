#include "ui/views/FileActionHandler.hpp"
#include <fstream>
#include <filesystem>
#include <ncurses.h>
#include <cstdlib>

namespace ui {

    /** @brief Checks if a string ends with a given suffix.
     * @param str The string to check.
     * @param suffix The suffix to check for.
     * @return True if the string ends with the suffix, false otherwise.
     */
    static bool endsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
    
    /** @brief Constructor for the FileActionHandler class.
     * @param context The ExplorerContext containing the necessary context for file actions.
     */
    FileActionHandler::FileActionHandler(ExplorerContext& context)
    : _ctx(context) {}
    
    /** @brief Checks if a file name indicates an archive.
     * @param name The name of the file to check.
     * @return True if the file is an archive, false otherwise.
     */
    bool FileActionHandler::isArchive(const std::string& name) {
        return endsWith(name, ".zip") || endsWith(name, ".tar") ||
               endsWith(name, ".gz")  || endsWith(name, ".rar");
    }

    /** @brief Creates a new file in the current directory.
     * Prompts the user for a file name and creates an empty file with that name.
     */
    void FileActionHandler::createNewFile() {
        NcursesWrapper& wrapper = _ctx.manager.getWrapper();
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        WINDOW* inputWin = wrapper.createWindow(3, 50, max_y - 3, 0);
        box(inputWin, 0, 0);
        wrapper.drawTextInWindow(inputWin, 1, 2, "Nom du fichier: ");
        wrapper.refreshWindow(inputWin);

        char filename[256];
        echo(); wgetnstr(inputWin, filename, 255); noecho();
        wrapper.destroyWindow(inputWin);

        std::string path = _ctx.directory.getPath() + "/" + filename;
        if (std::filesystem::exists(path)) {
            wrapper.drawTextInWindow(_ctx.manager.getWindow(WindowRole::EXPLORER), 0, 0, "Fichier déjà existant !");
            return;
        }

        std::ofstream file(path);
        file.close();

        _ctx.fileNames = _ctx.directory.listFiles();
        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Creates a new directory in the current directory.
     * Prompts the user for a directory name and creates a new directory with that name.
     */
    void FileActionHandler::createNewDirectory() {
        NcursesWrapper& wrapper = _ctx.manager.getWrapper();
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        WINDOW* inputWin = wrapper.createWindow(3, 50, max_y - 3, 0);
        box(inputWin, 0, 0);
        wrapper.drawTextInWindow(inputWin, 1, 2, "Nom du dossier: ");
        wrapper.refreshWindow(inputWin);

        char dirname[256];
        echo(); wgetnstr(inputWin, dirname, 255); noecho();
        wrapper.destroyWindow(inputWin);

        std::string path = _ctx.directory.getPath() + "/" + dirname;
        if (std::filesystem::exists(path)) {
            wrapper.drawTextInWindow(_ctx.manager.getWindow(WindowRole::EXPLORER), 0, 0, "Dossier déjà existant !");
            return;
        }

        std::filesystem::create_directory(path);
        _ctx.fileNames = _ctx.directory.listFiles();
        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Deletes the currently selected file or directory.
     * If the selected item is a directory, it will be removed recursively.
     * Updates the file list and switches back to the explorer view.
     */
    void FileActionHandler::deleteSelected() {
        if (_ctx.fileNames.empty()) return;
        std::string name = _ctx.fileNames[_ctx.selectedIndex];
        std::string path = _ctx.directory.getPath() + "/" + name;

        try {
            std::filesystem::directory_entry entry(path);
            if (entry.is_directory())
                std::filesystem::remove_all(path);
            else
                std::filesystem::remove(path);

            _ctx.fileNames = _ctx.directory.listFiles();
            if (_ctx.selectedIndex >= static_cast<int>(_ctx.fileNames.size()))
                _ctx.selectedIndex = std::max(0, static_cast<int>(_ctx.fileNames.size()) - 1);
        } catch (...) {
            _ctx.manager.drawText(0, 0, 0, "Erreur: suppression échouée");
        }

        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Renames the currently selected file or directory.
     * Prompts the user for a new name and renames the selected item.
     * If the new name already exists, an error message is displayed.
     */
    void FileActionHandler::renameSelected() {
        if (_ctx.fileNames.empty()) return;

        std::string oldName = _ctx.fileNames[_ctx.selectedIndex];
        std::string oldPath = _ctx.directory.getPath() + "/" + oldName;

        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        WINDOW* inputWin = newwin(3, 50, max_y - 3, 0);
        box(inputWin, 0, 0);
        mvwprintw(inputWin, 1, 2, "Nouveau nom : ");
        wrefresh(inputWin);

        char newName[256];
        echo(); wgetnstr(inputWin, newName, 255); noecho();
        delwin(inputWin);

        std::string newPath = _ctx.directory.getPath() + "/" + newName;
        if (std::filesystem::exists(newPath)) {
            _ctx.manager.drawText(0, 0, 0, "Erreur: le fichier existe déjà !");
            return;
        }

        std::filesystem::rename(oldPath, newPath);
        _ctx.fileNames = _ctx.directory.listFiles();
        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Zips the currently selected file or directory.
     * If the selected item is a directory, it will be zipped recursively.
     * Updates the file list and switches back to the explorer view.
     */
    void FileActionHandler::zipSelected() {
        if (_ctx.fileNames.empty()) return;
        std::string name = _ctx.fileNames[_ctx.selectedIndex];
        std::string src = _ctx.directory.getPath() + "/" + name;
        std::string dest = src + ".zip";

        std::string command = "zip -r \"" + dest + "\" \"" + src + "\"";
        if (system(command.c_str()) == 0)
            _ctx.fileNames = _ctx.directory.listFiles();
        else
            _ctx.manager.drawText(0, 0, 0, "Erreur lors du zip");

        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Unzips the currently selected zip archive.
     * If the selected item is not a zip file, an error message is displayed.
     * Updates the file list and switches back to the explorer view.
     */
    void FileActionHandler::unzipSelected() {
        if (_ctx.fileNames.empty()) return;
        std::string name = _ctx.fileNames[_ctx.selectedIndex];
        if (!endsWith(name, ".zip")) {
            _ctx.manager.drawText(0, 0, 0, "Pas une archive zip !");
            return;
        }

        std::string src = _ctx.directory.getPath() + "/" + name;
        std::string dest = _ctx.directory.getPath() + "/unzipped_" + name.substr(0, name.size() - 4);
        std::string command = "unzip \"" + src + "\" -d \"" + dest + "\"";

        if (system(command.c_str()) == 0)
            _ctx.fileNames = _ctx.directory.listFiles();
        else
            _ctx.manager.drawText(0, 0, 0, "Erreur lors du unzip");

        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Navigates back to the parent directory.
     * If already at the root, an error message is displayed.
     * Updates the file list and switches back to the explorer view.
     */
    void FileActionHandler::goBackToParent() {
        auto current = std::filesystem::path(_ctx.directory.getPath());
        if (current.has_parent_path()) {
            _ctx.directory.setPath(current.parent_path().string());
            _ctx.fileNames = _ctx.directory.listFiles();
            _ctx.selectedIndex = 0;
        } else {
            _ctx.manager.drawText(0, 0, 0, "Déjà à la racine.");
        }

        _ctx.switchCallback(ViewType::EXPLORER);
    }

    /** @brief Copies the currently selected file or directory.
     * The copied path is stored in the context for later pasting.
     */
    void FileActionHandler::copySelected() {
        if (_ctx.fileNames.empty()) return;
        std::string selected = _ctx.fileNames[_ctx.selectedIndex];
        _ctx.copiedPath = _ctx.directory.getPath() + "/" + selected;
    }

    /** @brief Pastes the previously copied file or directory into the current directory.
     * If a file with the same name already exists, it will be overwritten.
     * Updates the file list and switches back to the explorer view.
     */
    void FileActionHandler::pasteCopied() {
        if (!_ctx.copiedPath.has_value()) return;

        std::filesystem::path source(_ctx.copiedPath.value());
        std::filesystem::path dest = std::filesystem::path(_ctx.directory.getPath()) / source.filename();

        try {
            if (std::filesystem::is_directory(source)) {
                std::filesystem::copy(source, dest, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
            } else {
                std::filesystem::copy_file(source, dest, std::filesystem::copy_options::overwrite_existing);
            }
            _ctx.fileNames = _ctx.directory.listFiles();
        } catch (...) {
            _ctx.manager.drawText(0, 0, 0, "Erreur: collage échoué");
        }

        _ctx.switchCallback(ViewType::EXPLORER);
    }

} // namespace ui
