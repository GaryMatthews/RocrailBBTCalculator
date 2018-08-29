
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QResizeEvent>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

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

    ui->locImage->installEventFilter(this);
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

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->locImage && event->type() == QEvent::Resize)
    {
        auto resizeEvent = dynamic_cast<QResizeEvent *>(event);

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
    originalLocImage = locImage;

    ui->locImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->locImage->setPixmap(
        originalLocImage.scaled(ui->locImage->size(), Qt::KeepAspectRatio));
}
