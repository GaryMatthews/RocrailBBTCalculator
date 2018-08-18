
#include <QtWidgets/QtWidgets>

#include "core.hpp"

using BBTCalculator::Core::Core;

void Core::initializeApplication()
{
    setupTranslator();
    m_mainWindow.show();
}

void Core::setupTranslator()
{
    if (translator.load(QLocale(), QLatin1String("rocrailBBT"), QLatin1String("_"), QLatin1String("./gui/")))
    {
        QApplication::installTranslator(&translator);
        m_mainWindow.retranlateUi();
    }
}
