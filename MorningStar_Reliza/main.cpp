#include "morningstar.h"

#include <QApplication>
#include <QIcon>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MorningStar window;
    window.setWindowTitle("MorningStar: Reliza");
    window.setWindowIcon(QIcon(":/morningstar_resources/icons/ms_icon.png"));
    window.setFixedSize(300,350);
    window.show();

    return application.exec();
}
