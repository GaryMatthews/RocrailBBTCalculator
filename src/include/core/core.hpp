
#pragma once

#include <memory>

#include <QtCore/QTranslator>

#include "gui/locmodel.hpp"

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

            void displayImageForLocName(const QString& locName);

        private:
            void setupTranslator();

            std::shared_ptr<BBTCalculator::Gui::MainWindow> mainWindow;

            QTranslator translator;

            Workspace workspace;

            std::unique_ptr<Gui::LocModel> locModel;

        };
    } // namespace Core
} // namespace BBTCalculator
