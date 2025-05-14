#ifndef SIDEBAR_VIEW_HPP
    #define SIDEBAR_VIEW_HPP

    #include "ui/NcursesManager.hpp"
    #include "IView.hpp"
    #include "ViewType.hpp"

    #include <functional>
    #include <vector>
    #include <string>

namespace ui {

    /**
     * @class SidebarView
     * @brief A class that represents the sidebar view in the application.
     *
     * This class provides methods for handling user input, updating the UI,
     * and switching between different views in the application.
     */

    class SidebarView : public IView {
    public:
        SidebarView(NcursesManager& manager, std::function<void(ViewType)> onSwitch);

        void update() override;
        void handleInput(int ch) override;

    private:
        NcursesManager& _manager;
        std::function<void(ViewType)> _onSwitch;
        std::vector<std::string> _options = { "Explorer", "Quitter" };
        size_t _selectedIndex = 0;

        void drawMenu();
    };

} // namespace ui

#endif // SIDEBAR_VIEW_HPP
