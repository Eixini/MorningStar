#include "morningstar.h"

MorningStar::MorningStar(QWidget *parent): QWidget(parent)
{

   QVBoxLayout *vbox = new QVBoxLayout(this); // создание вертикального компоновщика
   vbox->setSpacing(3); // Установка расстояния между

   // +++++++++++++++++++++++++++  Создание кнопок и установка их размера  ++++++++++++++++++++++++++++++++++++++++++++++

   nettime = new QPushButton("Точное время", this); // создание кнопки для получения точного времени из интернета
   nettime->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding); // установка политики размера (увеличение вместе с главным окном)
   nettime->setIcon(QIcon(":/morningstar_resources/icons/clock_icon")); // устанавливает иконку в кнопку

   noteButton = new QPushButton("Заметки", this); // создание кнопки для меню заметок
   noteButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // установка политики размера (увеличение вместе с главным окном)
   noteButton->setIcon(QIcon(":/morningstar_resources/icons/clipboard_icon")); // устанавливает иконку в кнопку

   timer = new QPushButton("Таймер", this); // создание кнопки для установки таймера
   timer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // установка политики размера (увеличение вместе с главным окном)
   timer->setIcon(QIcon(":/morningstar_resources/icons/timer_icon")); // устанавливает иконку в кнопку

   randnum = new QPushButton("Случайное число", this); // создание кнопки для генерации случайного числа в настраиваемом диапозоне
   randnum->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); // установка политики размера (увеличение вместе с главным окном)
   randnum->setIcon(QIcon(":/morningstar_resources/icons/ball_icon")); // устанавливает иконку в кнопку

   info = new QPushButton("О Приложении", this); // создание кнопки для вывода информации о приложении
   info->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding); // установка политики размера (увеличение вместе с главным окном)
   info->setIcon(QIcon(":/morningstar_resources/icons/info_icon")); // устанавливает иконку в кнопку

   quit = new QPushButton("Выход", this); // создание кнопки для выхода из приложения
   quit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // установка политики размера (увеличение вместе с главным окном)
   quit->setIcon(QIcon(":/morningstar_resources/icons/door_icon")); // установка иконки для кнопки
   quit->setShortcut(tr("Alt+Q")); // установка горячей клавиши для кнопки выхода, при нажатии комбинации Alt+

   connect(quit, &QPushButton::clicked, qApp, &QApplication::quit); // при нажатии на кнопку "Выход" приложение будет закрываться
   connect(info, &QPushButton::clicked, this, &MorningStar::showInfo); // открытие окна с информацией
   connect(randnum, &QPushButton::clicked, this, &MorningStar::showRand); // открытие окна с генерацией случайного числа
   connect(timer, &QPushButton::clicked, this, &MorningStar::showTimer); // открытие окна с установкой таймера
   connect(noteButton, &QPushButton::clicked, this, &MorningStar::showNote); // открытие окна со списком заметок
   connect(nettime, &QPushButton::clicked, this, &MorningStar::showNettime); // открытие окна для получения точного времени из интернета

   // ++++++++++++++++++++++++++++  Добавление кнопок в вертикальный компоновщик  ++++++++++++++++++++++++++++++++++++++++

    vbox->addWidget(nettime);
    vbox->addWidget(noteButton);
    vbox->addWidget(timer);
    vbox->addWidget(randnum);
    vbox->addWidget(info);
    vbox->addWidget(quit);

    setLayout(vbox); // установка вертикального компоновщика (в качестве главного) на главное окно

}

void MorningStar::showInfo()
{
    class info infoWin;

    infoWin.setModal(true);
    infoWin.setFixedSize(300,410); // установка фиксированного размера
    infoWin.setWindowTitle("О Приложении"); // установка заголовка окна
    infoWin.setWindowIcon(QIcon(":/morningstar_resources/icons/info_icon")); // Установка иконки для окна

    infoWin.exec();
}

void MorningStar::showRand()
{
    class randnum randWin;

    randWin.setModal(true);
    randWin.setWindowTitle("Случайное число"); // Установка заголовка для окна
    randWin.setWindowIcon(QIcon(":/morningstar_resources/icons/ball_icon")); // установка иконки для окна
    randWin.setFixedSize(250,180); // установка фиксированного размера
    randWin.exec();
}

void MorningStar::showTimer()
{
    class timer timerWin;

    timerWin.setModal(true);
    timerWin.setWindowTitle("Таймер");
    timerWin.setWindowIcon(QIcon(":/morningstar_resources/icons/timer_icon"));
    timerWin.exec();
}


void MorningStar::showNote()
{
    class note noteWin;

    noteWin.setModal(true);
    noteWin.setWindowTitle("Заметки");
    noteWin.setWindowIcon(QIcon(":/morningstar_resources/icons/clipboard_icon"));
    noteWin.note_read(); // вызов метода для чтения заметок из файла

    noteWin.exec();
}

void MorningStar::showNettime()
{
    class nettime nettimeWin;

    nettimeWin.setModal(true);
    nettimeWin.setWindowTitle("Точное время");
    nettimeWin.setWindowIcon(QIcon(":/morningstar_resources/icons/clock_icon"));

    nettimeWin.exec();
}

MorningStar::~MorningStar() {}

