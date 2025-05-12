/**
 * @file FileInfoView.hpp
 * @brief Declaration of the ui::FileInfoView class that provides functionality for the file information view.
 */

#ifndef FILEINFOVIEW_HPP
    #define FILEINFOVIEW_HPP

    #include "ui/NcursesManager.hpp"
    #include "core/File.hpp"
    #include "IView.hpp"
    #include "ViewType.hpp"

    #include <functional>

namespace ui {

    /**
     * @class FileInfoView
     * @brief A class that represents the file information view in the application.
     *
     * This class provides methods for handling user input and updating the file information view.
     */
    class FileInfoView : public IView {
    public:
        FileInfoView(NcursesManager& manager, const core::File& file, std::function<void(ViewType)> switchCallback);

        void handleInput(int ch) override;
        void update() override;

    protected:
    private:
        NcursesManager& _manager;
        std::function<void(ViewType)> _switchCallback;
        core::File _file;

        std::string formatSize(std::uintmax_t size) const;
        std::string formatTime(std::time_t time) const;
    };

} // namespace ui

#endif // FILEINFOVIEW_HPP
