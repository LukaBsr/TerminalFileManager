#include "ui/views/FileInfoView.hpp"

namespace ui {

    FileInfoView::FileInfoView(NcursesManager& manager, std::function<void(ViewType)> switchCallback)
        : _manager(manager), _switchCallback(switchCallback) {}

    void FileInfoView::handleInput(int ch) {
        if (ch == 'b') {
            _switchCallback(ViewType::MAIN_MENU);
        }
    }

    void FileInfoView::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 1, 2, "[INFO FICHIER]");
        _manager.drawText(0, 3, 2, "Pas encore connecté à un fichier réel.");
        _manager.drawText(0, 5, 2, "Appuie sur 'b' pour revenir.");
        _manager.refreshAll();
    }

} // namespace ui
