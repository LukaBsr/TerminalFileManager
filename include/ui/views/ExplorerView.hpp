#ifndef EXPLORERVIEW_HPP
    #define EXPLORERVIEW_HPP

    #include "IView.hpp"
    #include "ui/NcursesManager.hpp"
    #include "ViewType.hpp"

    #include <functional>

namespace ui {

    class ExplorerView : public IView {
    public:
        ExplorerView(NcursesManager& manager, std::function<void(ViewType)> switchCallback);

        void handleInput(int ch) override;
        void update() override;

    protected:
    private:
        NcursesManager& _manager;
        std::function<void(ViewType)> _switchCallback;
    };

} // namespace ui

#endif // EXPLORERVIEW_HPP
