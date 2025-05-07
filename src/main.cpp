/**
 * @file main.cpp
 * @brief Entry point for the Terminal File Manager application.
 * @author [Boissiere Luka]
 * @date 2025-05-06
 */

#include "core/Directory.hpp"
#include "ui/NcursesApp.hpp"

int main()
{
    core::Directory dir(".");
    ui::NcursesApp app;

    app.run();
    return 0;
}
