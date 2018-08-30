
#pragma once

#include <memory>

#include <QtCore/QTranslator>
#include <QtCore/QSortFilterProxyModel>

#include "gui/blockmodel.hpp"
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

            void initializeApplication(Gui::MainWindowController& contr);

            void letUserSelectWorkspace();

            void displayImageForLocName(const QString& locName);

        private:
            void setupTranslator();

            std::shared_ptr<Gui::MainWindow> mainWindow;

            QTranslator translator;

            Workspace workspace;

            std::unique_ptr<Gui::LocModel> locModel;
            std::unique_ptr<Gui::BlockModel> blockModel;

            std::unique_ptr<QSortFilterProxyModel> locSortFilterModel;
            std::unique_ptr<QSortFilterProxyModel> blockSortFilterModel;
        };
    } // namespace Core
} // namespace BBTCalculator
