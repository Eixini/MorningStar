#include "morningstar.h"

#include <QApplication>
#include <QIcon>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName("MorningStar: Reliza");
    application.setApplicationVersion("v1.0 (Reliza)");
    application.setOrganizationName("Eixini Software");

    MorningStar window;
    window.setWindowTitle("MorningStar: Reliza");
    window.setWindowIcon(QIcon(":/morningstar_resources/icons/ms_icon.png"));
    window.setFixedSize(300,350);
    window.show();

    return application.exec();
}
