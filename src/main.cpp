/**
 * @file main.cpp
 * @brief Entry point for the Terminal File Manager application.
 * @author [Boissiere Luka]
 * @date 2025-05-06
 */

 #include "core/Directory.hpp"
 #include <iostream>
 
int main()
{
    core::Directory dir(".");

    std::cout << "📁 Contenu du répertoire courant :\n";
    for (const auto& name : dir.listFiles()) {
        std::cout << " - " << name << '\n';
    }

    return 0;
}
