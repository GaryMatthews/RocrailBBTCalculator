
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "core/core.hpp"
#include "gui/mainwindowcontroller.hpp"

using BBTCalculator::Core::Core;
using BBTCalculator::Gui::MainWindowController;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("mrpilot");
    QApplication::setOrganizationDomain("http://github.com/mrpilot2");
    QApplication::setApplicationName("rocrailBBTCalculator");
    QApplication::setApplicationDisplayName("Rocrail BBT Calculator");

    Q_INIT_RESOURCE(application);

    Core core{};

    MainWindowController controller{};
    controller.setCore(&core);

    core.initializeApplication(controller);

    return QApplication::exec();
}