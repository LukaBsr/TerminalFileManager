/**
 * @file Directory.cpp
 * @brief Implementation of the core::Directory class
 * @author [Boissiere Luka]
 * @date 2025-05-07
 */

#include "core/Directory.hpp"
#include <filesystem>
#include <stdexcept>

namespace core {

    Directory::Directory(const std::string& path)
        : _path(path)
    {
        refresh();
    }

    const std::string& Directory::getPath() const noexcept
    {
        return _path;
    }

    void Directory::setPath(const std::string& path)
    {
        _path = path;
        refresh();
    }

    bool Directory::exists() const noexcept
    {
        return std::filesystem::exists(_path);
    }

    bool Directory::create() const noexcept
    {
        return std::filesystem::create_directory(_path);
    }

    bool Directory::remove() const noexcept
    {
        return std::filesystem::remove_all(_path) > 0;
    }

    std::vector<std::string> Directory::listFiles() const noexcept
    {
        std::vector<std::string> names;

        for (const auto& file : _files)
            names.push_back(file.getName());
        return names;
    }

    void Directory::refresh()
    {
        _files.clear();
        if (!exists())
            return;

        for (const auto& entry : std::filesystem::directory_iterator(_path)) {
            _files.emplace_back(entry);
        }
    }

}
