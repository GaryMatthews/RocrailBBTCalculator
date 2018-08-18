
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "core/core.hpp"

using BBTCalculator::Core::Core;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("mrpilot");
    QApplication::setOrganizationDomain("http://github.com/mrpilot2");
    QApplication::setApplicationName("rocrailBBTCalculator");
    QApplication::setApplicationDisplayName("Rocrail BBT Calculator");

    Core core{};

    core.initializeApplication();

    return QApplication::exec();
}