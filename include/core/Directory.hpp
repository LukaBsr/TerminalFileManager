
/**
 * @file Directory.hpp
 * @brief Declaration of the core::Directory class that provides functionality for managing directories.
 */

#ifndef DIRECTORY_HPP
    #define DIRECTORY_HPP

    #include "core/File.hpp"

    #include <string>
    #include <vector>

namespace core {

    class Directory {
    public:
        // Constructor / Destructor
        explicit Directory(const std::string& path);
        ~Directory() = default;

        // Directory management
        bool exists() const noexcept;
        bool create() const noexcept;
        bool remove() const noexcept;

        // File operations
        std::vector<std::string> listFiles() const noexcept;
        void refresh(); // rescans directory and updates _files

        // Getters / Setters
        const std::string& getPath() const noexcept;
        void setPath(const std::string& path);

    private:
        std::string _path;
        std::vector<File> _files;
    };

} // namespace core

#endif // DIRECTORY_HPP
