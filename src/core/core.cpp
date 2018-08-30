#include <memory>

#include "core.hpp"

#include <QtWidgets/QtWidgets>

#include "gui/mainwindow.hpp"
#include "gui/mainwindowcontroller.hpp"

#include "planparser.hpp"

using BBTCalculator::Core::Core;
using BBTCalculator::Gui::MainWindow;
using BBTCalculator::Gui::MainWindowController;

Core::Core::Core()
    : mainWindow{new MainWindow()}
{
    letUserSelectWorkspace();
}

void Core::initializeApplication(MainWindowController& contr)
{
    mainWindow->setController(&contr);
    setupTranslator();
    mainWindow->show();
}

void Core::setupTranslator()
{
    if (translator.load(QLocale(), QLatin1String("rocrailBBT"),
                        QLatin1String("_"), QLatin1String("./gui/")))
    {
        QApplication::installTranslator(&translator);
        mainWindow->retranslateUi();
    }
}

void BBTCalculator::Core::Core::letUserSelectWorkspace()
{
    QString userSelectedDirectory = QString(
        "/home/markus/rocrail/MeinPlan");  // mainWindow->letUserSelectWorkspaceDirectory();

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
            workspace.setBlockList(parser.getBlockList());

            locModel = std::make_unique<Gui::LocModel>(workspace.getLocList());
            blockModel = std::make_unique<Gui::BlockModel>(workspace.getBlockList());

            mainWindow->setLocTableModel(locModel.get());
            mainWindow->setBlockTableModel(blockModel.get());
        }
        else
        {
            mainWindow->notifyUserSelectedDirectoryDoesNotExist();
        }
    }
}

void Core::displayImageForLocName(const QString& locName)
{
    const LocList& locList = workspace.getLocList();

    const auto search = [locName](const Loc& item) {
        return item.name == locName;
    };

    auto it = std::find_if(locList.begin(), locList.end(), search);

    if (it != locList.end())
    {
        QFileInfo fileInfo(workspace.getImagePath() + it->imageName);

        if (fileInfo.exists() && fileInfo.isFile())
        {
            QPixmap locImage{fileInfo.absoluteFilePath()};

            mainWindow->displayLocImage(locImage);
        }
    }
}
