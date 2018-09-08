#include "core.hpp"

#include <memory>

#include <QtWidgets/QtWidgets>

#include "gui/mainwindow.hpp"
#include "gui/mainwindowcontroller.hpp"

#include "calculation.hpp"
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
        "/home/markus/rocrailMeinPlan/"); // mainWindow->letUserSelectWorkspaceDirectory();

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
            workspace.setRouteList(parser.getRouteList());

            locModel = std::make_unique<Gui::LocModel>(workspace.getLocList());
            blockModel =
                std::make_unique<Gui::BlockModel>(workspace.getBlockList());
            routeModel =
                std::make_unique<Gui::RouteModel>(workspace.getRouteList());

            locSortFilterModel = std::make_unique<QSortFilterProxyModel>();
            blockSortFilterModel = std::make_unique<QSortFilterProxyModel>();
            routeSortFilterModel = std::make_unique<QSortFilterProxyModel>();

            locSortFilterModel->setSourceModel(locModel.get());
            blockSortFilterModel->setSourceModel(blockModel.get());
            routeSortFilterModel->setSourceModel(routeModel.get());

            mainWindow->setLocTableModel(locSortFilterModel.get());
            mainWindow->setBlockTableModel(blockSortFilterModel.get());
            mainWindow->setRouteTableModel(routeSortFilterModel.get());
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

void Core::createBBTModel(const QString& locName)
{
    const LocList& locList = workspace.getLocList();

    const auto search = [locName](Loc item) { return item.name == locName; };

    auto it = std::find_if(locList.begin(), locList.end(), search);

    if (it != locList.end())
    {
        bbtModel = std::make_unique<Gui::BBTModel>(it->bbt);

        bbtSortFilterModel = std::make_unique<QSortFilterProxyModel>();
        bbtSortFilterModel->setSourceModel(bbtModel.get());

        mainWindow->setBBTTableModel(bbtSortFilterModel.get());

        mainWindow->setLocNameInBBTBox(it->name);
    }
}

void Core::filterBlockByMainline(int column)
{
    filterBlockAndRouteByMainline(blockSortFilterModel.get(), column);
}

void Core::filterRouteByMainline(int column)
{
    filterBlockAndRouteByMainline(routeSortFilterModel.get(), column);
}

void Core::removeBlockAndRouteMainlineFilter()
{
    blockSortFilterModel->setFilterRegExp("");
    routeSortFilterModel->setFilterRegExp("");
}

void Core::filterBlockAndRouteByMainline(QSortFilterProxyModel* model, int column)
{
    model->setFilterKeyColumn(column);
    model->setFilterRegExp("true");
}

void Core::calculateBBT(const QString& locName)
{
    LocList& locList = workspace.getLocList();

    const auto search = [locName](Loc item) { return item.name == locName; };

    auto it = std::find_if(locList.begin(), locList.end(), search);

    if (it != locList.end())
    {
        if (not it->bbt.empty())
        {
            int returnCode = mainWindow->askUserIfExistingBBTEntriesShallBeDeleted();
            if (returnCode == QMessageBox::Cancel) {
                return;
            }
            if (returnCode == QMessageBox::Yes) {
                it->bbt.clear();
            }
        }

        BlockList& blockList{workspace.getBlockList()};
        RouteList& routeList{workspace.getRouteList()};

        Calculation calc{&(*it), routeList, blockList};
        calc.calculateNewBBTEntries(mainWindow->getUserSelectedCorrectionFactor());

        createBBTModel(locName);

        PlanParser parser(workspace.getPlanFilePath());
        parser.saveBBTForLocomotive(*it);
    }
}
