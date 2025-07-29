/**
 * @file ViewType.hpp
 * @brief Declaration of the ui::ViewType enum class that defines different view types.
 */

#ifndef VIEWTYPE_HPP
    #define VIEWTYPE_HPP

namespace ui {

    /**
     * @enum ViewType
     * @brief Defines the different views available in the application.
     */
    enum class ViewType {
        MAIN_MENU,
        EXPLORER,
        FILE_INFO,
        QUIT
    };

} // namespace ui

#endif
