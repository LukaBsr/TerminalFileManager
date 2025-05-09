#ifndef FILEINFOVIEW_HPP
    #define FILEINFOVIEW_HPP

    #include "IView.hpp"
    #include "ui/NcursesManager.hpp"
    #include "ViewType.hpp"

    #include <functional>

namespace ui {

    class FileInfoView : public IView {
    public:
        FileInfoView(NcursesManager& manager, std::function<void(ViewType)> switchCallback);

        void handleInput(int ch) override;
        void update() override;

    protected:
    private:
        NcursesManager& _manager;
        std::function<void(ViewType)> _switchCallback;
    };

} // namespace ui

#endif // FILEINFOVIEW_HPP
