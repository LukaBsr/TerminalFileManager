/**
 * @file NcursesApp.hpp
 * @brief Declaration of the ui::NcursesApp class that provides functionality for managing the main application loop and user interactions.
 */

#ifndef NCURSESAPP_HPP
    #define NCURSESAPP_HPP

    #include "ui/NcursesManager.hpp"
    #include "views/ViewType.hpp"
    #include "views/IView.hpp"
    #include "views/SidebarView.hpp"
    #include "views/ExplorerView.hpp"
    #include "views/FileInfoView.hpp"

    #include <memory>
    #include <functional>
    #include <vector>
    #include <string>
    #include <mutex>

namespace ui {

    /**
     * @struct MenuOption
     * @brief A structure that represents a menu option with a label and an action.
     *
     * This structure is used to define the options available in the menu, including
     * the label to be displayed and the action to be executed when the option is selected.
     */
    
    struct MenuOption {
        std::string label;
        std::function<void()> action;
    };

    /**
     * @class NcursesApp
     * @brief A class that manages the main application loop and user interactions.
     *
     * This class provides methods for running the application, handling user input,
     * updating the UI, and managing the ncurses library.
     */

    class NcursesApp {
    public:
        NcursesApp();
        ~NcursesApp();

        void run();

        void setSelectedFile(std::shared_ptr<core::File> file);
        std::shared_ptr<core::File> getSelectedFile() const;

    protected:
    private:
        NcursesWrapper _wrapper;
        NcursesManager _manager;

        std::mutex _fileMutex;
        std::shared_ptr<core::File> _selectedFile;
        std::unique_ptr<IView> _currentView;
        bool _running;

        std::vector<MenuOption> _menuOptions;
        int _selectedIndex;

        void switchView(ViewType type);
        void handleUserInput();
        void update();
        void initLayout();
    };

} // namespace ui

#endif
