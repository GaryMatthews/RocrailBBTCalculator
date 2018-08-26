
#pragma once

#include <memory>

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

            void retranslateUi();

            auto letUserSelectWorkspaceDirectory() -> QString;

            void notifyUserSelectedDirectoryDoesNotExist();

            void showRootPath(const QString& path);

        private:
            void setupMenuActions();

            void connectSignals();

            Ui::MainWindow* ui;

            MainWindowController* controller;
        };
    } // namespace Gui
} // namespace BBTCalculator