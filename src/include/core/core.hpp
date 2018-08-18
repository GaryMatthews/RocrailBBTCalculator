
#pragma once

#include <memory>

#include <QtCore/QTranslator>

#include "gui/mainwindow.hpp"

namespace BBTCalculator::Core
{
    class Core
    {
    public:
        void initializeApplication();

    private:
        void setupTranslator();

        BBTCalculator::Gui::MainWindow m_mainWindow;

        QTranslator translator;

    };
}
