
#include <mainwindowcontroller.hpp>

#include "mainwindowcontroller.hpp"

#include "core/core.hpp"

using BBTCalculator::Core::Core;
using BBTCalculator::Gui::MainWindowController;

MainWindowController::MainWindowController() :
    core{nullptr}
{

}

void MainWindowController::setCore(BBTCalculator::Core::Core* c)
{
    core = c;
}

void MainWindowController::onOpenWorkspaceClicked(bool)
{
    core->letUserSelectWorkspace();
}
