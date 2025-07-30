#pragma once

#include "ExplorerContext.hpp"
#include <string>

namespace ui {

    /**
     * @class FileActionHandler
     * @brief A class that handles file actions in the explorer view.
     *
     * This class provides methods for creating, deleting, renaming, zipping, unzipping,
     * navigating directories, copying, and pasting files in the explorer view.
     */
    class FileActionHandler {
    public:
        FileActionHandler(ExplorerContext& context);

        bool isArchive(const std::string& name);

        void createNewFile();
        void createNewDirectory();
        void deleteSelected();
        void renameSelected();
        void zipSelected();
        void unzipSelected();
        void goBackToParent();
        void copySelected();
        void pasteCopied();

    private:
        ExplorerContext& _ctx;
    };

} // namespace ui
