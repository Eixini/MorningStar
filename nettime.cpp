#include "nettime.h"

nettime::nettime(QDialog *parent) : QDialog(parent)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~  ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное меню
    requestButton = new QPushButton("Запросить", this); // Создание кнопки для запроса времени из интернета

    // Создание LCD для отображения часов, минут и секунд
    hLCD = new QLCDNumber(this);
    mLCD = new QLCDNumber(this);
    sLCD = new QLCDNumber(this);

    // Создание текстовых метод для подписи LCD
    hlabel = new QLabel("Hour",this);
    mlabel = new QLabel("Minute",this);
    slabel = new QLabel("Second",this);

    labCityText = new QLabel("Выбранный город: ", this); // Создание текстовой метки
    selectCity = new QLabel("",this); // Создание текстовой метки для установки название выбранного города

    nettimeList = new QComboBox(this); // Создание выпадающего списка для городов (часовых поясов)

    grid = new QGridLayout(); // Создание сетчатого компоновщика
    vbox = new QVBoxLayout(); // Создание вертикального компоновщика
    vboxLab = new QVBoxLayout(); // Создание вертикального компоновщика
    hbox = new QHBoxLayout(this); // Создание горизонтального компоновщика

    net = new QNetworkAccessManager(this);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ОТЛАДОЧНАЯ ФИГНЯ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cityTime = "http://worldtimeapi.org/api/timezone/Europe/Moscow";

    // +++++++++++++++++++++++++   НАСТРОЙКА ФУНКЦИОНАЛА   ++++++++++++++++++++++++++++++

    // Установка количество символов в LCD
    hLCD->setDigitCount(2);
    mLCD->setDigitCount(2);
    sLCD->setDigitCount(2);

    // Установка стиля для LCD
    hLCD->setSegmentStyle(QLCDNumber::Flat);
    mLCD->setSegmentStyle(QLCDNumber::Flat);
    sLCD->setSegmentStyle(QLCDNumber::Flat);

    //Добавление городов (часовых поясов) в список
    nettimeList->addItem("Калининград (МСК -1)");
    nettimeList->addItem("Москва (МСК 0)");
    nettimeList->addItem("Самара (МСК +1)");
    nettimeList->addItem("Екатеринбург (МСК +2)");
    nettimeList->addItem("Омск (МСК +3)");
    nettimeList->addItem("Новосибирск (МСК +4)");
    nettimeList->addItem("Иркутск (МСК +5)");
    nettimeList->addItem("Якутск (МСК +6)");
    nettimeList->addItem("Хабаровск (МСК +7)");
    nettimeList->addItem("Дружина (МСК +8)");
    nettimeList->addItem("Анадырь (МСК +9)");

    //selectCity->setText(nettimeList->itemText); // Устанавливает название выбранного города (часового пояса) из списка ComboBox

    // ***********************  ПОДКЛЮЧЕНИЕ СИГНАЛОВ К СЛОТАМ  **************************

    connect(mainmenu, &QPushButton::clicked, this, &QDialog::accept); // При нажатии на кнопку будет произведен возврат в главное меню
    connect(requestButton, &QPushButton::clicked, this, &nettime::TimeRequest);
    connect(net, &QNetworkAccessManager::finished, this, &nettime::onFinished);

    // ^^^^^^^^^^^^^^^^^^^^^^^     УПРАВЛЕНИЕ КОМПОНОВКОЙ     ^^^^^^^^^^^^^^^^^^^^^^^^^^^

    // Добавление виджетов в сетку (виджет, строка в компоновщике, столбец в компоновщике)

    grid->addWidget(hlabel, 0, 0, Qt::AlignHCenter);
    grid->addWidget(mlabel, 0, 1, Qt::AlignHCenter);
    grid->addWidget(slabel, 0, 2, Qt::AlignHCenter);
    grid->addWidget(hLCD, 1, 0);
    grid->addWidget(mLCD, 1, 1);
    grid->addWidget(sLCD, 1, 2);

    vbox->addLayout(grid);
    vbox->addWidget(requestButton, Qt::AlignHCenter);
    vbox->addWidget(mainmenu);

    vboxLab->addWidget(labCityText, Qt::AlignHCenter);
    vboxLab->addWidget(selectCity);
    vboxLab->addWidget(nettimeList);
    vboxLab->addStretch(1); // Добавление коэффициента растяжения снизу

    hbox->addLayout(vbox);
    hbox->addLayout(vboxLab);

    setLayout(hbox); // Установка главного компоновщика

}

void nettime::TimeRequest()
{
    // Для запроса времени из интернета
    QMessageBox::warning(this,"Информация","Происходит запрос данных.");
    net->get(QNetworkRequest(QUrl(cityTime))); // запрос на данные

}

void nettime::onFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QMessageBox::warning(this,"Информация","Получены данные, идет обработка.");
        QJsonDocument testData = QJsonDocument::fromJson(reply->readAll()); // Присваивание переменной типа QString полученных данных
        // Для отладки. Запись в файл полученных данных.
        QString loc = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); // СОздание строки, хранящей в себе путь к рабочему столу
        QFile filenettime(loc + "/timetext.txt"); // Создание файла ПУТЬ + ИМЯ ФАЙЛА
        filenettime.open(QFile::WriteOnly);

        // Надо извлеч даннные из наборы (ключ:значение) - datetime, и присвоить объекту типа QTime

        QString timeValue = testData["datetime"].toString(); // Извлечение из JSON данных нужный элемент (через ключ)
        QDateTime date = QDateTime::fromString(timeValue); // Присваивание извлеченных данных объекту для даты и времени
        QTime time = date.time(); // Попытка извлечения времени

        // Установка значений из QDateTime в дсиплеи
        hLCD->display(time.hour());
        mLCD->display(time.minute());
        sLCD->display(time.second());

        // В ЦЕЛЯХ ОТЛАДКИ
        QString test = date.toString();
        QMessageBox::warning(this, "ПРоверка", testData["datetime"].toString());

        filenettime.write(timeValue.toUtf8()); // запись в файл
        filenettime.close();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка",reply->errorString());
    }

    reply->deleteLater();
}

nettime::~nettime() {}
