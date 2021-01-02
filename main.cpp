#include "morningstar.h"

#include <QApplication>
#include <QSplashScreen>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Предзагрузочное окно  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    QSplashScreen *splash = new QSplashScreen; // создание объекта презагрузочного окна
    splash->setPixmap(QPixmap("/home/eixini/Рабочий стол/Eixini/Qt/Projects/MorningStar/File_for_Project/loading_logo.png")); // установка изображения на предзагрузочное окно
    splash->show(); // показ предзагрузочного окна


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   Главное окно   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    MorningStar window; // создание главного окна
    window.setWindowTitle("Morning Star v. Zero"); // установка заголовка на главное окно
    window.setWindowIcon(QIcon("/home/eixini/Рабочий стол/Eixini/Qt/Projects/MorningStar/File_for_Project/ms_icon")); // установка иконки для главного окна
    window.setFixedSize(300,250); // установка размера главного окна



        window.show();
        splash->close(); // закрытие предзагрузочного окна

        return app.exec();
    }
