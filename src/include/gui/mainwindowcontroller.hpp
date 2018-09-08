
#pragma once

#include <QtCore/QObject>
#include <QtCore/QItemSelection>

namespace BBTCalculator
{
    namespace Core
    {
        class Core;
    } // namespace Core
} // namespace BBTCalculator

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

            void onLocSelectionChanged(const QItemSelection& selected,
                                       const QItemSelection& deselected);

            void onFilterMainlineStateChanged(int state);

            void onUserRequestsBBTCalculation();

        private:
            BBTCalculator::Core::Core* core;
        };
    } // namespace Gui
} // namespace BBTCalculator