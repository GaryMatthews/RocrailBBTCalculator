
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("mrpilot");
    QApplication::setOrganizationDomain("http://github.com/mrpilot2");
    QApplication::setApplicationName("rocrailBBTCalculator");

    return QApplication::exec();
}