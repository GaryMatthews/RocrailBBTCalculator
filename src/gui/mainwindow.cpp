
#include "mainwindow.hpp"

#include <QResizeEvent>

#include <QtCore/QSettings>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "bbtmodel.hpp"
#include "blockmodel.hpp"
#include "locmodel.hpp"
#include "ui_mainwindow.h"

using BBTCalculator::Gui::MainWindow;

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

    ui->blockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->blockTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->blockTable->setSortingEnabled(true);
    ui->blockTable->horizontalHeader()->setStretchLastSection(true);

    ui->bbtTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bbtTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bbtTable->setSortingEnabled(true);
    ui->bbtTable->horizontalHeader()->setStretchLastSection(true);

    ui->locImage->installEventFilter(this);

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
    QWidget::closeEvent(event);
}

void MainWindow::connectSignals()
{
    connect(ui->actionOpenWorkspace, &QAction::triggered, controller,
            &MainWindowController::onOpenWorkspaceClicked);
    connect(ui->locList->selectionModel(),
            &QItemSelectionModel::selectionChanged, controller,
            &MainWindowController::onLocSelectionChanged);
}

auto MainWindow::letUserSelectWorkspaceDirectory() -> QString
{
    return QFileDialog::getExistingDirectory(
        this, tr("Select Rocrail workspace"), QDir::homePath(),
        QFileDialog::ShowDirsOnly);
}

void MainWindow::notifyUserSelectedDirectoryDoesNotExist()
{
    QMessageBox::critical(this, tr("Workspace directory not found"),
                          tr("The selected workspace directory does not"
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
}

void MainWindow::setBlockTableModel(QAbstractItemModel* model)
{
    ui->blockTable->setModel(model);

    ui->blockTable->resizeColumnsToContents();
    ui->blockTable->sortByColumn(static_cast<int>(BlockViewColumns::NAME),
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
}
