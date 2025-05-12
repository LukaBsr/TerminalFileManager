/**
 * @file File.cpp
 * @brief Implementation of the fman::core::File class
 * @author [Boissiere Luka]
 * @date 2025-05-06
 */

#include "core/File.hpp"
#include <chrono>

namespace core {

    File::File(const std::filesystem::directory_entry& entry)
        : _name(entry.path().filename().string()),
          _path(entry.path().string()),
          _size(entry.is_regular_file() ? entry.file_size() : 0),
          _isDirectory(entry.is_directory())
    {
        // Get last modification time and convert to time_t
        auto ftime = entry.last_write_time();
        auto systemTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now()
            + std::chrono::system_clock::now());
        _lastModified = std::chrono::system_clock::to_time_t(systemTime);
    }

    const std::string& File::getName() const noexcept { 
        return _name; 
    }

    const std::string& File::getPath() const noexcept { 
        return _path; 
    }

    std::uintmax_t File::getSize() const noexcept { 
        return _size; 
    }

    bool File::isDirectory() const noexcept { 
        return _isDirectory; 
    }

    std::time_t File::getLastModified() const noexcept { 
        return _lastModified; 
    }

}
