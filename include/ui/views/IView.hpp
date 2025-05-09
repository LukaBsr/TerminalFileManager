/**
 * @file IView.hpp
 * @brief Declaration of the ui::IView interface that provides a contract for view classes.
 */

#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "ui/NcursesManager.hpp"

namespace ui {

    /**
     * @class IView
     * @brief An interface that defines the contract for view classes in the application.
     *
     * This interface provides methods for handling user input and updating the view.
     */

    class IView {
    public:
        virtual ~IView() = default;

        virtual void handleInput(int ch) = 0;
        virtual void update() = 0;
    
    protected:
    private:
    };

} // namespace ui

#endif // IVIEW_HPP
