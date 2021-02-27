#include "timer.h"

timer::timer(QDialog *parent) : QDialog(parent)
{
    // +++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ +++++++++++++++++++++++++

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в меню
    setTimerButton = new QPushButton("Установить", this); // Создание кнопки для установки значения таймера
    startTimerButton = new QPushButton("Запуск", this); // Создание кнопки для запуска таймера
    cancelTimerButton = new QPushButton("Отмена", this); // Создание кнопки для отмены таймера

    thour = new QSpinBox(this); // Создание спинбокса для установки часов в таймер
    tminut = new QSpinBox(this); // СОздание спинбокса для установки минут в таймер

    minutLCD = new QLCDNumber(this); // Создание LCD для отображения времени на таймере (минуты)
    hourLCD = new QLCDNumber(this); // Создание  LCD для отображения времени на таймере (часы)

    hboxSpinbox = new QHBoxLayout(); // создание горизонтального компоновщика для спинбоксов
    hboxLCD = new QHBoxLayout(); // создание горизонтального компоновщика для LCD
    hboxLabel = new QHBoxLayout(); // создание горизонтального компоновщика для текстовых меток
    vbox = new QVBoxLayout(this); // создание вертикального компоновщика (для последующего его установки в качестве главного)

    labmin = new QLabel("Minute", this); // Создание текстовой метки для подписи lcd (минуты)
    labhour = new QLabel("Hour", this); // Создание текстовой метки для подписи lcd (часы)

    timer_val = new QTimer; // Создание таймера

    // Со временем не помешает добавить прогрессБар

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ НАСТРОЙКА КОМПОНЕНТОВ ~~~~~~~~~~~~~~~~~~~~~~~~~

    minutLCD->setSegmentStyle(QLCDNumber::Flat); // Установка стиля отображаемого значения для LCD
    hourLCD->setSegmentStyle(QLCDNumber::Flat);

    minutLCD->setDigitCount(2); // Установка количество сегментов в LCD
    hourLCD->setDigitCount(2);

    minutLCD->display(0); // Установка значения в LCD
    hourLCD->display(0);

    tminut->setRange(0,59); // Установка диапозона для спинбокса ответсвенного за ввод количесвта минут

    timer_val->setInterval(1000); // Установка интервала дя таймера


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~ ПОДКЛЮЧЕНИЕ КНОПОК ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    connect(mainmenu, &QPushButton::clicked, this, &QDialog::accept); // СОздание сигнала-слота кнопки дял возврата в главное меню

    connect(setTimerButton, &QPushButton::clicked, this, &timer::LCDValueMin); // Применение значения со Спинбокса(мин) на LCD (мин)
    connect(setTimerButton, &QPushButton::clicked,this, &timer::LCDValueHour); // Применение значения со Спинбокса(час) на LCD (час)
    connect(startTimerButton, &QPushButton::clicked, this, &timer::startTimer); // Запуск таймера
    connect(cancelTimerButton, &QPushButton::clicked, this, &timer::cancelTimer);
   // =========================== УПРАВЛЕНИЕ КОМПОНОВКОЙ =========================


    hboxSpinbox->addWidget(thour);
    hboxSpinbox->addWidget(tminut);

    hboxLCD->addWidget(hourLCD);
    hboxLCD->addWidget(minutLCD);

    hboxLabel->addWidget(labhour, 1 , Qt::AlignCenter);
    hboxLabel->addWidget(labmin, 1 , Qt::AlignCenter);

    vbox->addSpacing(30); // Добавление расстояние между элементами в компоновщике
    vbox->addLayout(hboxLabel);
    vbox->addLayout(hboxLCD);
    vbox->addLayout(hboxSpinbox);
    vbox->addWidget(setTimerButton);
    vbox->addWidget(startTimerButton);
    vbox->addWidget(cancelTimerButton);
    vbox->addWidget(mainmenu, 1, Qt::AlignBottom);

    setLayout(vbox); // Установка Вертикального компоновщика в качестве главного
}

void timer::startTimer()
{
    long minute; // переменная для хранения количество введеных минут
    long hour; // переменная для хранения количество введеных часов

    minute = tminut->value(); // получение значения со SpinBox
    hour = thour->value();

    long long msec_val; // переменная для хранения миллисекунд

    msec_val = minuteTomsec(minute) + hourTomsec(hour); // суммирование количесво минут и часов , переведенных в миллисекунды

    timer_val->start(msec_val); // старт таймера
    connect(timer_val,&QTimer::timeout, this, &timer::showMessage);
}

void timer::cancelTimer()
{
    timer_val->stop(); // Остановка таймера

    minutLCD->display(0); // Очистка показателя lcd
    hourLCD->display(0);
}

void timer::LCDValueMin()
{
    // Установка значения со Спинбокса на LCD Минут

    int valmin;

    valmin = tminut->value();
    minutLCD->display(valmin);
}

void timer::LCDValueHour()
{
    // Установка значения со Спинбокса на LCD часов

    int valhour;

    valhour = thour->value();
    hourLCD->display(valhour);
}

long timer::minuteTomsec(long minuteVal)
{
    return minuteVal * 1000 * 60; // количество минут умножаем на количесвво мсек и сек в 1 минуте
}

long long timer::hourTomsec(long hourVal)
{
    return hourVal * 1000 * 60 * 60; // количество часов умножаем на количество мсек, сек и минут в 1 часе
}

void timer::showMessage()
{
    QMessageBox::warning(this, "Внимание","Время вышло");
}

timer::~timer(){}
