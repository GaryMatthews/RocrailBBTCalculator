
#pragma once

#include <memory>

#include <QtCore/QTranslator>

#include "workspace.hpp"

namespace BBTCalculator::Gui
{
    class MainWindowController;
    class MainWindow;
}

namespace BBTCalculator::Core
{
    class Core
    {
    public:
        Core();

        void initializeApplication(BBTCalculator::Gui::MainWindowController& contr);

        void letUserSelectWorkspace();

    private:
        void setupTranslator();

        std::shared_ptr<BBTCalculator::Gui::MainWindow> mainWindow;

        QTranslator translator;

        Workspace workspace;

    };
}
