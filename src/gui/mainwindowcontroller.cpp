
#include <mainwindowcontroller.hpp>

#include "mainwindowcontroller.hpp"

#include "core/core.hpp"

using BBTCalculator::Core::Core;
using BBTCalculator::Gui::MainWindowController;

MainWindowController::MainWindowController() :
    core{nullptr}
{}

void MainWindowController::setCore(BBTCalculator::Core::Core *c)
{
    core = c;
}

void MainWindowController::onOpenWorkspaceClicked(bool)
{
  core->letUserSelectWorkspace();
}

void MainWindowController::onLocSelectionChanged(const QItemSelection& selected,
                                                 const QItemSelection& deselected)
{
    const QItemSelectionRange& singleRow{selected.at(0)};

    core->displayImageForLocName(singleRow.indexes().at(LocViewColumns::NAME).data().toString());
}
