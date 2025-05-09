#include "ui/views/ExplorerView.hpp"

namespace ui {

    ExplorerView::ExplorerView(NcursesManager& manager, std::function<void(ViewType)> switchCallback)
        : _manager(manager), _switchCallback(switchCallback) {}

    void ExplorerView::handleInput(int ch) {
        if (ch == 'b') {
            _switchCallback(ViewType::MAIN_MENU);
        }
    }

    void ExplorerView::update() {
        _manager.clearWindow(0);
        _manager.drawText(0, 1, 2, "[EXPLORER]");
        _manager.drawText(0, 3, 2, "Contenu fictif à explorer...");
        _manager.drawText(0, 5, 2, "Appuie sur 'b' pour revenir.");
        _manager.refreshAll();
    }

} // namespace ui
