
#pragma once

#include <memory>

#include <QtCore/QTranslator>

#include "workspace.hpp"

namespace BBTCalculator
{
    namespace Gui
    {
        class MainWindowController;

        class MainWindow;
    } // namespace Gui
} // namespace BBTCalculator

namespace BBTCalculator
{
    namespace Core
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
    } // namespace Core
} // namespace BBTCalculator
