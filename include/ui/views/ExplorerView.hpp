/**
 * @file ExplorerView.hpp
 * @brief Declaration of the ui::ExplorerView class that provides functionality for the explorer view.
 */

#ifndef EXPLORERVIEW_HPP
    #define EXPLORERVIEW_HPP

    #include "ui/NcursesManager.hpp"
    #include "core/Directory.hpp"
    #include "IView.hpp"
    #include "ViewType.hpp"
    #include "FileActionHandler.hpp"

namespace ui {

    class NcursesApp;
    
    /**
     * @class ExplorerView
     * @brief A class that represents the explorer view in the application.
     *
     * This class provides methods for handling user input and updating the explorer view.
     */
    class ExplorerView : public IView {
    public:
        ExplorerView(NcursesManager& manager, NcursesApp& parent, std::function<void(ViewType)> switchCallback);

        void handleInput(int ch) override;
        void update() override;

    protected:
    private:
        core::Directory _directory;
        std::vector<std::string> _fileNames;
        std::optional<std::string> _copiedPath;
        int _selectedIndex;

        NcursesManager& _manager;
        NcursesApp& _parent;

        std::unique_ptr<FileActionHandler> _actionHandler;
        std::unique_ptr<ExplorerContext> _context;
        std::function<void(ViewType)> _switchCallback;

        void enterSelected();
    
    };

} // namespace ui

#endif // EXPLORERVIEW_HPP
