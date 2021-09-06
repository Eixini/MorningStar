#include "morningstar.h"

#include <QApplication>
#include <QSplashScreen>
#include <QIcon>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Предзагрузочное окно  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    QSplashScreen *splash = new QSplashScreen; // создание объекта презагрузочного окна
    splash->setPixmap(QPixmap(":/morningstar_resources/images/morningstar_splashscreen")); // установка изображения на предзагрузочное окно
    splash->show(); // показ предзагрузочного окна

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   Главное окно   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    MorningStar window; // создание главного окна
    QApplication::setStyle("windows"); // установка стиля для приложения
    window.setWindowTitle("Morning Star v. Zero"); // установка заголовка на главное окно
    window.setWindowIcon(QIcon(":/morningstar_resources/icons/ms_icon")); // установка иконки для главного окна
    window.setFixedSize(300,250); // установка размера главного окна

    window.show();
    splash->close(); // закрытие предзагрузочного окна

    return app.exec();
}
