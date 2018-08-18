
#pragma once

#include "gui/mainwindow.hpp"

#include <memory>

namespace BBTCalculator::Core
{
    class Core
    {
    public:
        void initializeApplication();

    private:
        BBTCalculator::Gui::MainWindow m_mainWindow;
    };
}
