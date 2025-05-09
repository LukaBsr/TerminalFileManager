/**
 * @file ExplorerView.hpp
 * @brief Declaration of the ui::ExplorerView class that provides functionality for the explorer view.
 */

#ifndef EXPLORERVIEW_HPP
    #define EXPLORERVIEW_HPP

    #include "IView.hpp"
    #include "ui/NcursesManager.hpp"
    #include "ViewType.hpp"

    #include <functional>

namespace ui {

    /**
     * @class ExplorerView
     * @brief A class that represents the explorer view in the application.
     *
     * This class provides methods for handling user input and updating the explorer view.
     */
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
