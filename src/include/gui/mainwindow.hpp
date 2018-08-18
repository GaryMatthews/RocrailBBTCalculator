
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
        Ui::MainWindow* m_ui;
    };
}