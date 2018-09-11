
#include "mainwindow.hpp"

#include <QResizeEvent>

#include <QtCore/QSettings>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "bbtmodel.hpp"
#include "blockmodel.hpp"
#include "locmodel.hpp"
#include "routemodel.hpp"
#include "ui_mainwindow.h"

using BBTCalculator::Gui::MainWindow;
using BBTCalculator::Gui::MainWindowController;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMenuActions();

    ui->locList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->locList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->locList->setSortingEnabled(true);
    ui->locList->horizontalHeader()->setStretchLastSection(true);
    ui->locList->horizontalHeader()->setSectionsMovable(true);

    ui->blockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->blockTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->blockTable->setSortingEnabled(true);
    ui->blockTable->horizontalHeader()->setStretchLastSection(true);
    ui->blockTable->horizontalHeader()->setSectionsMovable(true);

    ui->routesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->routesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->routesTable->setSortingEnabled(true);
    ui->routesTable->horizontalHeader()->setStretchLastSection(true);
    ui->routesTable->horizontalHeader()->setSectionsMovable(true);

    ui->bbtTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bbtTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bbtTable->setSortingEnabled(true);
    ui->bbtTable->horizontalHeader()->setStretchLastSection(true);
    ui->bbtTable->horizontalHeader()->setSectionsMovable(true);

    ui->locImage->installEventFilter(this);

    ui->calculateBBT->setEnabled(false);
    ui->correctionFactorDescription->setEnabled(false);
    ui->correctionFactor->setEnabled(false);
    ui->showMainlineOnly->setEnabled(false);

    QSettings settings;
    this->restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setController(MainWindowController* contr)
{
    controller = contr;
    connectSignals();

    QSettings settings;
    ui->showMainlineOnly->setChecked(
        settings.value("showMainLineOnly", false).toBool());
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->locImage && event->type() == QEvent::Resize)
    {
        auto resizeEvent = dynamic_cast<QResizeEvent*>(event);

        if (ui->locImage->pixmap() != nullptr)
        {
            ui->locImage->setPixmap(originalLocImage.scaled(
                resizeEvent->size(), Qt::KeepAspectRatio));
            return true;
        }
        return false;
    }
    return QObject::eventFilter(watched, event);
}

void MainWindow::setupMenuActions()
{
    ui->actionClose->setShortcuts(QKeySequence::Quit);
    ui->actionOpenWorkspace->setShortcuts(QKeySequence::Open);
}

void MainWindow::retranslateUi()
{
    ui->retranslateUi(this);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings;
    settings.setValue("mainwindow/geometry", this->saveGeometry());

    settings.setValue("showMainLineOnly", ui->showMainlineOnly->isChecked());
    QWidget::closeEvent(event);
}

void MainWindow::connectSignals()
{
    connect(ui->actionOpenWorkspace, &QAction::triggered, controller,
            &MainWindowController::onOpenWorkspaceClicked);
    connect(ui->showMainlineOnly, &QCheckBox::stateChanged, controller,
            &MainWindowController::onFilterMainlineStateChanged);
    connect(ui->calculateBBT, &QPushButton::clicked, controller,
            &MainWindowController::onUserRequestsBBTCalculation);
}

auto MainWindow::letUserSelectWorkspaceDirectory() -> QString
{
    return QFileDialog::getExistingDirectory(
        this, QApplication::translate("MainWindow", "Select Rocrail workspace"),
        QDir::homePath(), QFileDialog::ShowDirsOnly);
}

void MainWindow::notifyUserSelectedDirectoryDoesNotExist()
{
    QMessageBox::critical(
        this,
        QApplication::translate("MainWindow", "Workspace directory not found"),
        QApplication::translate("MainWindow",
                                "The selected workspace directory does not"
                                "exist."));
}

void MainWindow::showRootPath(const QString& path)
{
    this->setWindowTitle(path);
}

void MainWindow::setLocTableModel(QAbstractItemModel* model)
{
    ui->locList->setModel(model);

    ui->locList->resizeColumnsToContents();
    ui->locList->sortByColumn(static_cast<int>(LocViewColumns::NAME),
                              Qt::AscendingOrder);
    connect(ui->locList->selectionModel(),
            &QItemSelectionModel::selectionChanged, controller,
            &MainWindowController::onLocSelectionChanged);
}

void MainWindow::setBlockTableModel(QAbstractItemModel* model)
{
    ui->blockTable->setModel(model);

    ui->blockTable->resizeColumnsToContents();
    ui->blockTable->sortByColumn(static_cast<int>(BlockViewColumns::NAME),
                                 Qt::AscendingOrder);
    ui->showMainlineOnly->setEnabled(true);
    controller->onFilterMainlineStateChanged(ui->showMainlineOnly->checkState());
}

void MainWindow::setRouteTableModel(QAbstractItemModel* model)
{
    ui->routesTable->setModel(model);

    ui->routesTable->resizeColumnsToContents();
    ui->routesTable->sortByColumn(static_cast<int>(RouteViewColumns::NAME),
                                  Qt::AscendingOrder);
}

void MainWindow::displayLocImage(QPixmap& locImage)
{
    originalLocImage = locImage;

    ui->locImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->locImage->setPixmap(
        originalLocImage.scaled(ui->locImage->size(), Qt::KeepAspectRatio));
}

void BBTCalculator::Gui::MainWindow::setBBTTableModel(QAbstractItemModel* model)
{
    ui->bbtTable->setModel(model);

    ui->bbtTable->resizeColumnsToContents();
    ui->bbtTable->sortByColumn(static_cast<int>(BBTViewColumns::BLOCK),
                               Qt::AscendingOrder);

    ui->calculateBBT->setEnabled(true);
    ui->correctionFactorDescription->setEnabled(true);
    ui->correctionFactor->setEnabled(true);
}

void MainWindow::setLocNameInBBTBox(const QString& locName)
{
    ui->bbtBox->setTitle(
        "BBT - " + locName + " (" +
        QString::number(ui->bbtTable->model()->rowCount()) + " " +
        QApplication::translate("MainWindow", "entries") + ")");
}

auto MainWindow::getUserSelectedCorrectionFactor() const -> double
{
    return ui->correctionFactor->value();
}

auto MainWindow::askUserIfExistingBBTEntriesShallBeDeleted() -> int
{
    return QMessageBox::warning(
        this, QApplication::translate("MainWindow", "Existing BBT entries"),
        QApplication::translate("MainWindow",
                                "There are some BBT entries stored for this "
                                "locomotive.\nShall they "
                                "be overwritten?"),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
}
