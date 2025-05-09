#ifndef MAINMENUVIEW_HPP
    #define MAINMENUVIEW_HPP

    #include "IView.hpp"
    #include "ui/NcursesManager.hpp"
    #include "ViewType.hpp"

    #include <functional>
    #include <vector>
    #include <string>

namespace ui {

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
