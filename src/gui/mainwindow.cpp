
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <mainwindow.hpp>


using BBTCalculator::Gui::MainWindow;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMenuActions();
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
    connect(ui->actionOpenWorkspace, &QAction::triggered, controller, &MainWindowController::onOpenWorkspaceClicked);
}

auto MainWindow::letUserSelectWorkspaceDirectory() -> QString
{
    return QFileDialog::getExistingDirectory(this, tr("Select Rocrail workspace"), QDir::homePath(),
                                             QFileDialog::ShowDirsOnly);
}

void MainWindow::notifyUserSelectedDirectoryDoesNotExist()
{
    QMessageBox::critical(this, tr("Workspace directory not found"), tr("The selected workspace directory does not"
                                                                        "exist."));
}

void MainWindow::showRootPath(const QString& path)
{
    this->setWindowTitle(path);
}
