/**
 * @file File.hpp
 * @brief Declaration of the fman::core::File class that encapsulates file metadata
 */

#ifndef FILE_HPP
    #define FILE_HPP

    #include <string>
    #include <filesystem>

namespace fman::core {

    class File {
    public:
        explicit File(const std::filesystem::directory_entry& entry);

        const std::string& name() const noexcept;
        const std::string& path() const noexcept;
        std::uintmax_t size() const noexcept;
        bool isDirectory() const noexcept;
        std::time_t lastModified() const noexcept;

    protected:
    private:
        std::string _name;
        std::string _path;
        std::uintmax_t _size;
        bool _isDirectory;
        std::time_t _lastModified;
    };

}

#endif // FILE_HPP