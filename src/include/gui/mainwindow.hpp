
#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>

namespace Ui
{
    class MainWindow;
}

namespace BBTCalculator::Gui
{
    class MainWindow : public QMainWindow
    {
    public:
        explicit MainWindow(QWidget* parent = nullptr);

        ~MainWindow() override;

    private:
        void setupMenuActions();

        Ui::MainWindow* ui;
    };
}