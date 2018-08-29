
#include "core.hpp"

#include <QtWidgets/QtWidgets>

#include "gui/mainwindow.hpp"
#include "gui/mainwindowcontroller.hpp"

#include "planparser.hpp"

using BBTCalculator::Core::Core;
using BBTCalculator::Gui::MainWindow;
using BBTCalculator::Gui::MainWindowController;

Core::Core::Core() :
    mainWindow{new MainWindow()}
{}

void Core::initializeApplication(MainWindowController& contr)
{
    mainWindow->setController(&contr);
    setupTranslator();
    mainWindow->show();
}

void Core::setupTranslator()
{
    if (translator.load(QLocale(), QLatin1String("rocrailBBT"), QLatin1String("_"), QLatin1String("./gui/")))
    {
        QApplication::installTranslator(&translator);
        mainWindow->retranslateUi();
    }
}

void BBTCalculator::Core::Core::letUserSelectWorkspace()
{
    QString userSelectedDirectory = mainWindow->letUserSelectWorkspaceDirectory();

    if (not userSelectedDirectory.isEmpty())
    {
        const QDir dir{userSelectedDirectory};
        if (dir.exists())
        {
            workspace.setRootPath(dir);
            mainWindow->showRootPath(dir.absolutePath());
            PlanParser parser(workspace.getPlanFilePath());
            parser.parse();

            workspace.setLocList(parser.getLocList());
        }
        else {
            mainWindow->notifyUserSelectedDirectoryDoesNotExist();
        }
    }
}
