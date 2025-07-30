// ExplorerContext.hpp
#pragma once

#include "ui/NcursesManager.hpp"
#include "core/Directory.hpp"
#include "ViewType.hpp"

#include <optional>
#include <functional>

namespace ui {

    class NcursesApp;

    /**
     * @struct ExplorerContext
     * @brief A structure that holds the context for the explorer view, including the manager, app, directory,
     * file names, selected index, switch callback, and copied path.
     *
     * This structure is used to pass necessary information to the explorer view and its associated actions.
     */
    struct ExplorerContext {
        NcursesManager& manager;
        NcursesApp& app;
        core::Directory& directory;
        std::vector<std::string>& fileNames;
        int& selectedIndex;
        std::function<void(ViewType)> switchCallback;
        std::optional<std::string>& copiedPath;
    };

} // namespace ui
