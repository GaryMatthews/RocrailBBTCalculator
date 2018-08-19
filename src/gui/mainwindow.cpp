
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

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

void MainWindow::setupMenuActions()
{
    ui->actionClose->setShortcuts(QKeySequence::Quit);
    ui->actionOpenWorkspace->setShortcuts(QKeySequence::Open);
}

void BBTCalculator::Gui::MainWindow::retranslateUi()
{
    ui->retranslateUi(this);
}
