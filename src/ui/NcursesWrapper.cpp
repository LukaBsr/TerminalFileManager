/**
 * @file NcursesWrapper.cpp
 * @brief Implementation of the ui::NcursesWrapper class
 * @author [Boissiere Luka]
 * @date 2025-05-07
 */

#include "ui/NcursesWrapper.hpp"

namespace ui {

    NcursesWrapper::NcursesWrapper() {}

    NcursesWrapper::~NcursesWrapper() {
        end();
    }

    void NcursesWrapper::init() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        halfdelay(10);
        start_color();
        use_default_colors();
        
        init_pair(1, COLOR_BLUE, -1);
        init_pair(2, COLOR_WHITE, -1);
        init_pair(3, COLOR_GREEN, -1);
        init_pair(4, COLOR_CYAN, -1);
        init_pair(5, COLOR_YELLOW, -1);
        
        refresh();
    }

    void NcursesWrapper::end() {
        endwin();
    }

    void NcursesWrapper::refresh() {
        ::refresh();
    }

    void NcursesWrapper::clear() {
        ::clear();
    }

    void NcursesWrapper::printText(int y, int x, const std::string& text) {
        mvprintw(y, x, "%s", text.c_str());
    }

    WINDOW* NcursesWrapper::createWindow(int height, int width, int startY, int startX) {
        return newwin(height, width, startY, startX);
    }

    void NcursesWrapper::destroyWindow(WINDOW* window) {
        if (window)
            delwin(window);
    }

    void NcursesWrapper::clearWindow(WINDOW* window) {
        if (window)
            wclear(window);
    }

    void NcursesWrapper::refreshWindow(WINDOW* window) {
        if (window)
            wrefresh(window);
    }

    void NcursesWrapper::drawTextInWindow(WINDOW* window, int y, int x, const std::string& text) {
        if (window)
            mvwprintw(window, y, x, "%s", text.c_str());
    }

    int NcursesWrapper::getChar() {
        return getch();
    }

} // namespace ui
