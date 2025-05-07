/**
 * @file File.hpp
 * @brief Declaration of the core::File class that encapsulates file metadata
 */

#ifndef FILE_HPP
    #define FILE_HPP

    #include <string>
    #include <filesystem>

namespace core {

    /**
     * @class File
     * @brief A class that represents a file and provides methods to access its metadata.
     *
     * This class encapsulates the metadata of a file, including its name, path,
     * size, type (file or directory), and last modified time.
     */

    class File {
    public:
        explicit File(const std::filesystem::directory_entry& entry);
        ~File() = default;

        const std::string& getName() const noexcept;
        const std::string& getPath() const noexcept;
        std::uintmax_t getSize() const noexcept;
        bool getIsDirectory() const noexcept;
        std::time_t getLastModified() const noexcept;

    protected:
    private:
        std::string _name;
        std::string _path;
        std::uintmax_t _size;
        bool _isDirectory;
        std::time_t _lastModified;
    };

} // namespace core

#endif // FILE_HPP
