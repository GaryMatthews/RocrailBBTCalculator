
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <mainwindow.hpp>

using BBTCalculator::Gui::MainWindow;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMenuActions();

    ui->locList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->locList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->locList->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setController(MainWindowController *contr)
{
    controller = contr;
    connectSignals();
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

void MainWindow::showRootPath(const QString &path)
{
    this->setWindowTitle(path);
}

void MainWindow::setLocTableModel(QAbstractTableModel *model)
{
    ui->locList->setModel(model);
}

void MainWindow::displayLocImage(QPixmap &locImage)
{
    ui->locImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->locImage->setPixmap(locImage.scaled(ui->locImage->size(), Qt::KeepAspectRatio));
}
