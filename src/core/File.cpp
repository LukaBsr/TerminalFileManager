/**
 * @file File.cpp
 * @brief Implementation of the fman::core::File class
 * @author [Boissiere Luka]
 * @date 2025-05-06
 */

#include "core/File.hpp"
#include <chrono>

namespace fman::core {

    // Constructor for the File class
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

    // Getter for the file name
    const std::string& File::name() const noexcept { 
        return _name; 
    }

    // Getter for the file path
    const std::string& File::path() const noexcept { 
        return _path; 
    }

    // Getter for the file size
    std::uintmax_t File::size() const noexcept { 
        return _size; 
    }

    // Check if the file is a directory
    bool File::isDirectory() const noexcept { 
        return _isDirectory; 
    }

    // Getter for the last modified time
    std::time_t File::lastModified() const noexcept { 
        return _lastModified; 
    }

}
