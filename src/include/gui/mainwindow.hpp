
#pragma once

#include <memory>

#include <QtCore/QAbstractTableModel>
#include <QtWidgets/QMainWindow>

#include "mainwindowcontroller.hpp"

namespace Ui
{
    class MainWindow;
} // namespace Ui

namespace BBTCalculator
{
    namespace Gui
    {
        class MainWindow : public QMainWindow
        {
        public:
            explicit MainWindow(QWidget* parent = nullptr);

            ~MainWindow() override;

            void setController(MainWindowController* contr);

            bool eventFilter(QObject* watched, QEvent* event) override;

            void retranslateUi();

            auto letUserSelectWorkspaceDirectory() -> QString;

            void notifyUserSelectedDirectoryDoesNotExist();

            void showRootPath(const QString& path);

            void setLocTableModel(QAbstractItemModel* model);

            void setBlockTableModel(QAbstractItemModel* model);

            void displayLocImage(QPixmap& locImage);

        private:
            void setupMenuActions();

            void connectSignals();

            Ui::MainWindow* ui;

            MainWindowController* controller;

            QPixmap originalLocImage;
        };
    } // namespace Gui
} // namespace BBTCalculator