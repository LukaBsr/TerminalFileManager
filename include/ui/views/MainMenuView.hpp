/**
 * @file MainMenuView.cpp
 * @brief Declaration of the ui::MainMenuView class that provides functionality for the main menu view.
 */

#ifndef MAINMENUVIEW_HPP
    #define MAINMENUVIEW_HPP

    #include "IView.hpp"
    #include "ui/NcursesManager.hpp"
    #include "ViewType.hpp"

    #include <functional>
    #include <vector>
    #include <string>

namespace ui {

    /**
     * @class MainMenuView
     * @brief A class that represents the main menu view in the application.
     *
     * This class provides methods for handling user input and updating the main menu view.
     */
    class MainMenuView : public IView {
    public:
        MainMenuView(NcursesManager& manager, std::function<void(ViewType)> switchCallback);

        void handleInput(int ch) override;
        void update() override;

    protected:
    private:
        NcursesManager& _manager;
        std::function<void(ViewType)> _switchCallback;

        std::vector<std::string> _options;
        int _selectedIndex;
    };

} // namespace ui

#endif // MAINMENUVIEW_HPP
