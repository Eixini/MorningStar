#include "timer.h"

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QSpacerItem>
#include <QTimer>
#include <QMessageBox>
#include <QIcon>
#include <QProgressBar>
#include <QThread>
#include <QSystemTrayIcon>

timer::timer(QDialog *parent) : QDialog(parent)
{
   // +++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ++++++++++++++++++++++++++
    {
    mainmenu = new QPushButton(tr("Вернуться в меню"), this); // Создание кнопки для возврата в меню
    setTimerButton = new QPushButton(tr("Установить"), this); // Создание кнопки для установки значения таймера
    startTimerButton = new QPushButton(tr("Запуск"), this); // Создание кнопки для запуска таймера
    cancelTimerButton = new QPushButton(tr("Отмена"), this); // Создание кнопки для отмены таймера

    hourNIXIE = new QNixieNumber(this, QNixieNumber::REALNIXIE);
    minuteNIXIE = new QNixieNumber(this, QNixieNumber::REALNIXIE);
    secondNIXIE = new QNixieNumber(this, QNixieNumber::REALNIXIE);

    thour = new QSpinBox(this);         // Создание спинбокса для установки часов в таймер
    tminut = new QSpinBox(this);        // Создание спинбокса для установки минут в таймер
    tsecond = new QSpinBox(this);       // Создание спинбокса для установки секунд в таймер

    vbox = new QVBoxLayout(this); // создание вертикального компоновщика (для последующего его установки в качестве главного)
    hboxSpinbox = new QHBoxLayout(); // создание горизонтального компоновщика для спинбоксов
    hboxNumber = new QHBoxLayout(); // создание горизонтального компоновщика для LCD
    hboxLabel = new QHBoxLayout(); // создание горизонтального компоновщика для текстовых меток

    timer_val = new QTimer(this); // Создание таймера

    pbar = new QProgressBar(this);

    trayicon = new QSystemTrayIcon(QIcon(":/morningstar_resources/icons/timer_icon.png"),this);
    }

   // ~~~~~~~~~~~~~~~~~~~~~~~~~ НАСТРОЙКА КОМПОНЕНТОВ ~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
    // Установка количество сегментов
    hourNIXIE->setSegmentsCount(2);
    minuteNIXIE->setSegmentsCount(2);
    secondNIXIE->setSegmentsCount(2);

    hourNIXIE->display(00);   // Установка значения в LCD
    minuteNIXIE->display(00);
    secondNIXIE->display(00);

    tminut->setRange(0,59); // Установка диапозона для спинбокса ответсвенного за ввод количесвта минут
    tsecond->setRange(0,59);

    pbar->setValue(0);
    }

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~ ПОДКЛЮЧЕНИЕ КНОПОК ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {

    connect(setTimerButton, &QPushButton::clicked, this, &timer::NumberValueMin); // Применение значения со Спинбокса(мин) на дисплей (мин)
    connect(setTimerButton, &QPushButton::clicked, this, &timer::NumberValueHour); // Применение значения со Спинбокса(час) на дисплей (час)
    connect(setTimerButton, &QPushButton::clicked, this, &timer::NumberValueSecond); // Применение значения со Спинбокса(сек) на дисплей (час)
    connect(startTimerButton, &QPushButton::clicked, this, &timer::startTimer);
    connect(cancelTimerButton, &QPushButton::clicked, this, &timer::cancelTimer);
    if(sumSec == 0)
        connect(mainmenu, &QPushButton::clicked, this, &QDialog::accept); // Создание сигнала-слота кнопки дял возврата в главное меню
    else
    {
        this->setModal(false);
        this->hide();
    }

    }

    // --------------------------- ОТЛАДОЧНОЕ ГОВНО ------------------------------


    // ======================== УПРАВЛЕНИЕ КОМПОНОВКОЙ ===========================
    {

    hboxSpinbox->addWidget(thour);
    hboxSpinbox->addWidget(tminut);
    hboxSpinbox->addWidget(tsecond);

    hboxNumber->addWidget(hourNIXIE);
    hboxNumber->addWidget(minuteNIXIE);
    hboxNumber->addWidget(secondNIXIE);

    vbox->addSpacing(30); // Добавление расстояние между элементами в компоновщике
    vbox->addLayout(hboxLabel);
    vbox->addLayout(hboxNumber);
    vbox->addWidget(pbar);
    vbox->addLayout(hboxSpinbox);
    vbox->addWidget(setTimerButton);
    vbox->addWidget(startTimerButton);
    vbox->addWidget(cancelTimerButton);
    vbox->addWidget(mainmenu);

    }

    setLayout(vbox); // Установка Вертикального компоновщика в качестве главного
}

void timer::startTimer()
{
    sumSec = (thour->value() * 3600) + (tminut->value() * 60) + tsecond->value();       // Суммирование (переведенных в секунды часы и минуты) секунд
    progBarValue = 0;

    pbar->setMinimum(0);
    pbar->setMaximum(sumSec);

    if(thour->value() == 0 &&  tminut->value()== 0 && tsecond->value() == 0)
        QMessageBox::warning(this,tr("Внимание! "),tr("Вы не установили время!"));

     timer_val->start(1000);                              // старт таймера
     connect(timer_val,&QTimer::timeout, this, &timer::updateTime);

}

void timer::cancelTimer()
{
    timer_val->stop();              // Остановка таймера

    hourNIXIE->display(0);          // Очистка показателя дисплея
    minuteNIXIE->display(0);
    secondNIXIE->display(0);
    pbar->setValue(0);              // Обнуление прогрессбара

    disconnect(timer_val,&QTimer::timeout, this, &timer::updateTime);
}

void timer::NumberValueMin()    { minuteNIXIE->display(tminut->value());  }       // Установка значения со Спинбокса на дисплей минут

void timer::NumberValueHour()   {  hourNIXIE->display(thour->value());   }        // Установка значения со Спинбокса на дисплей часов

void timer::NumberValueSecond() { secondNIXIE->display(tsecond->value());  }      // Установка значения со Спинбокса на дисплей секунд

long timer::minuteTomsec(long minuteVal) { return minuteVal * 1000 * 60; }      // Количество минут умножаем на количесвво мсек и сек в 1 минуте

long long timer::hourTomsec(long hourVal) { return hourVal * 1000 * 60 * 60; }  // Количество часов умножаем на количество мсек, сек и минут в 1 часе

int timer::secondTomsec(short secondVal) {return secondVal * 1000;  }           // Количество секунд умножается на количество мсек в 1 секунде

void timer::updateTime()
{
    if(sumSec > 0)
    {
        sumSec--;
        hourNIXIE->display(sumSec / 3600);
        minuteNIXIE->display((sumSec % 3600) / 60);
        secondNIXIE->display((sumSec % 3600) % 60);
        ++progBarValue;
        pbar->setValue(progBarValue);
    }
    else
        showMessage();
}

void timer::showMessage()
{
    if(trayicon->isSystemTrayAvailable())           // Проверка, поддерживается ли функционал данной ОС
    {
        trayicon->setVisible(true);
        trayicon->showMessage(tr("Таймер"), tr("Установленное время истекло!"));
    }
    else
        QMessageBox::warning(this, "Информация", "Время вышло!");

    cancelTimer();
}

timer::~timer(){}
