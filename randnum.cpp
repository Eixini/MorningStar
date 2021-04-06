#include "randnum.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

#include <ctime>

randnum::randnum(QDialog *parent) : QDialog(parent)
{
    // +++++++++++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ +++++++++++++++++++++++++++

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное меню
    generate = new QPushButton("Сгенерировать", this); // Создание кнопки для генерации числа

    shownum = new QLabel("",this); // Создание текстовой метки для отображения резульата
    errorRange = new QLabel("", this);

    vbox = new QVBoxLayout(this); // Добавление вериткального компоновщика
    hbox = new QHBoxLayout(); // Добавления горизонтального компоновщика для ввода диапозона
    vrange = new QVBoxLayout(); // Добавление вертикального компоновщика для отображения числа и настройки диапазона генерации

    smin = new QSpinBox(this); // Создание спинбокса дял ввода минимального
    smax = new QSpinBox(this); // Создание спинбокса для ввода максимального

    // ------------------------------------ НАСТРОЙКА ПАРАМЕТРОВ ------------------------------

    smin->setRange(0,INT_MAX-1); // Установка диапазона для ввода минимального значения
    smax->setRange(1,INT_MAX); // Установка диапазона для ввода максимального значения

    // ```````````````````````````````` настройка кнопки ````````````````````````````````

    connect(mainmenu, &QPushButton::clicked, this, &QDialog::accept); // Поключение кнопки для принятия результата и возврата в главное
    connect(generate,&QPushButton::clicked, this, &randnum::ShowResult);

    // ---------------------------- ПРОЦЕСС КОМПОНОВКИ _________________________________

    hbox->addWidget(smin);
    hbox->addWidget(smax);

    vrange->addWidget(shownum, 1 , Qt::AlignHCenter);
    vrange->addWidget(errorRange,1, Qt::AlignHCenter);
    vrange->addLayout(hbox);

    vbox->addLayout(vrange);
    vbox->addWidget(generate, 1, Qt::AlignHCenter);
    vbox->addWidget(mainmenu, 1 , Qt::AlignBottom);

    setLayout(vbox); // Установка вертикального компоновщика в качестве главного
}

void randnum::ShowResult()
{
    errorRange->clear();

    srand(time(0)); // Для обновления генерации чисел
    int RandNumber = 0; // Создание переменной, для хранения результата генерации случайного числа
    int min, max; // ПеременныеЮ для хранения минимального и максимального значения диапазона

    QString errorMSNG = "MAX должен быть больше MIN";
    QString error = "ERROR";

    min = smin->value(); // Конвертация из значения в спинбоксе в целочисленное
    max = smax->value(); // Конвертация из значения в спинбоксе в целочисленное

    if(max<=min) // не работает как надо
    {
        errorRange->setText(errorMSNG);
        shownum->setText(error);
    }
    else if(min == max)
    {
        errorRange->setText(errorMSNG);
        shownum->setText(error);
    }
   else
    {
        RandNumber = min + (rand() % (max - min)); // Генерация случайного числа и сохранения его в переменной
        shownum->setText(QString::number(RandNumber)); // Конвертация из int в qstring и уставнока в метке для отображения
    }


}


randnum::~randnum()
{
}
