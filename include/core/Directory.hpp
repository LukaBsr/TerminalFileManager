
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

    /**
     * @class Directory
     * @brief A class that represents a directory and provides methods for managing it.
     *
     * This class allows you to check if a directory exists, create or remove it,
     * list files within the directory, and refresh the file list.
     */

    class Directory {
    public:
        explicit Directory(const std::string& path);
        ~Directory() = default;

        bool exists() const noexcept;
        bool create() const noexcept;
        bool remove() const noexcept;

        std::vector<std::string> listFiles() const noexcept;
        void refresh(); // rescans directory and updates _files

        const std::string& getPath() const noexcept;
        void setPath(const std::string& path);

    private:
        std::string _path;
        std::vector<File> _files;
    };

} // namespace core

#endif // DIRECTORY_HPP
