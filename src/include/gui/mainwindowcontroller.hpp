
#pragma once

#include <QtCore/QObject>

namespace BBTCalculator
{
    namespace Core
    {
        class Core;
    }
}

namespace BBTCalculator
{
    namespace Gui
    {
        class MainWindowController : public QObject
        {
        Q_OBJECT
        public:
            MainWindowController();

            void setCore(BBTCalculator::Core::Core* core);

        public slots:

            void onOpenWorkspaceClicked(bool checked = false);

        private:
            BBTCalculator::Core::Core* core;
        };
    }
}