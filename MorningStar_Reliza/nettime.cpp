#include "nettime.h"

#include <QNetworkAccessManager>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCompleter>
#include <QNixieNumber/qnixienumber.h>
#include <QSystemTrayIcon>
#include <QTime>
#include <QUdpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QMap>
#include <QStandardPaths>
#include <QDir>

#include <QList>
#include <QVector>
#include <QThread>

#include <externals/date/date.h>
#include <externals/date/tz.h>
#include <externals/date/date.h>

// Классы для отладки
#include <QMessageBox>
#include <QTimeZone>
#include <QFile>
#include <QByteArray>

/*      Моменты, требующие внимания.

  - для tzdb методов загрузки и установки, сделать отдельный поток, чтобы приложение не замораживалось;
  - настроить компоновку виджетов;
  - сделать проверку на наличие базы данных, ее целостности и актуальности версии, если все ок, то не будет скачиваться и устанавливаться лишний раз;

*/

nettime::nettime(QDialog *parent) : QDialog(parent)
{
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ++++++++++++++++++++++++++++++++++++++++++++++++ */
    {
        hoursDisplay = new QNixieNumber(this, QNixieNumber::REALNIXIE);
        minutesDisplay = new QNixieNumber(this, QNixieNumber::REALNIXIE);
        secondsDisplay = new QNixieNumber(this, QNixieNumber::REALNIXIE);

        enterCityLine = new QLineEdit(this);
        completer = new QCompleter(this);

        labelSelectCity = new QLabel(this);
        labelCurrentSelectCity = new QLabel(this);

        headLayout = new QVBoxLayout(this);
        selectCity = new QHBoxLayout();
        buttonsLayout = new QHBoxLayout();
        displaysLayout = new QHBoxLayout();
        enterLineLayout = new QHBoxLayout();

        toMainMenuButton = new QPushButton(this);
        requestTimeButton = new QPushButton(this);

        // Директория, в которой будет хранится база данных часовых поясов, скаченная с помощью библиотеки tzdb
        pathDataTZ_DB = QString(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza" + "/DataTZ");

    }
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ НАСТРОЙКА ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        hoursDisplay->setSegmentsCount(2);
        minutesDisplay->setSegmentsCount(2);
        secondsDisplay->setSegmentsCount(2);

        hoursDisplay->display(0);
        minutesDisplay->display(0);
        secondsDisplay->display(0);

        labelSelectCity->setText(tr("Selected city: "));
        labelCurrentSelectCity->setText(tr(""));

        toMainMenuButton->setText(tr("Main menu"));
        requestTimeButton->setText(tr("Request time"));

        selectCity->setAlignment(Qt::AlignTop);
        enterLineLayout->setAlignment(Qt::AlignBottom);
        enterLineLayout->setSpacing(0);
        buttonsLayout->setAlignment(Qt::AlignBottom);

    }
    /* ====================================================== ПОДКЛЮЧЕНИЕ К СИГНАЛАМ ================================================ */
    {
    connect(toMainMenuButton, &QPushButton::clicked, this, &QDialog::accept);
    request_time();
    }
    /* ...................................................... УПРАВЛЕНИЕ КОМПОНОВКОЙ ................................................ */
    {
        selectCity->addWidget(labelSelectCity);
        selectCity->addWidget(labelCurrentSelectCity);

        displaysLayout->addWidget(hoursDisplay);
        displaysLayout->addWidget(minutesDisplay);
        displaysLayout->addWidget(secondsDisplay);

        enterLineLayout->addWidget(enterCityLine);

        buttonsLayout->addWidget(requestTimeButton);
        buttonsLayout->addWidget(toMainMenuButton);

        headLayout->addLayout(selectCity);
        headLayout->addLayout(displaysLayout);
        headLayout->addLayout(enterLineLayout);
        headLayout->addLayout(buttonsLayout);

        setLayout(headLayout);
    }

}

void nettime::request_time()
{
    // Запрос времени и получение результат
    unsigned char ntpPack[48] = {0x1b};

   QHostInfo hostinfo;
   QHostAddress adress;
   QUdpSocket socket;


   hostinfo = QHostInfo::fromName("1.europe.pool.ntp.org");
   adress =  QHostAddress(hostinfo.addresses().at(0));

   socket.writeDatagram((const char *)ntpPack ,48, adress, 123);            // Запись пакета
   while(socket.readDatagram((char*)ntpPack, 48) != 48);                    // Чтение полученного пакета

   quint32 transmit_seconds = ntpPack[40];
   transmit_seconds = transmit_seconds * 256 + ntpPack[41];
   transmit_seconds = transmit_seconds * 256 + ntpPack[42];
   transmit_seconds = transmit_seconds * 256 + ntpPack[43];

   quint32 unix_time = transmit_seconds - NTP_TIMESTAMP_DELTA;
   QDateTime timestamp;

   timestamp.setTimeSpec(Qt::UTC);
   timestamp.currentDateTimeUtc();
   timestamp.setTime_t(unix_time);

   QMessageBox::warning(this, "Info", timestamp.toString() );

   // ПОКА ЧТО ВРЕМЕННО - ВЫЗОВ СЛОТА БЕЗ КОННЕКТА
   tz_database();

}

void nettime::tz_database()
{
    // Проверять наличие существовании директории для хранения БД часовых поясов, если нет, то создавать
    QDir dataTZDBDir(pathDataTZ_DB);
    if(!dataTZDBDir.exists())
        dataTZDBDir.mkdir(pathDataTZ_DB);

    date::set_install(pathDataTZ_DB.toStdString());

    /*   !!! ЖЕЛАТЕЛЬНО БЫ ЗАГРУЗКУ И УСТАНОВКУ БАЗУ ДАННЫХ ЧАСОВЫХ ПОЯСОВ ПЕРЕКИНУТЬ В ДРУГОЙ ПОТОК !!!   */
    date::remote_download(date::remote_version());
    date::remote_install(date::remote_version());

//    QVector<date::time_zone> tz_vector = QVector<date::time_zone> (date::get_tzdb().zones.begin() , date::get_tzdb().zones.end());

    // НАЧАЛО ОТЛАДОЧНОГО БЛОКА. В целях отладки

    QFile test(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/test.txt");
    test.open(QIODevice::WriteOnly);

    for(auto n = 0; n < date::get_tzdb().zones.size(); ++n)
        test.write(QString::fromStdString(date::get_tzdb().zones.at(n).name()).toUtf8() + "\n");
    test.close();


    // КОНЕЦ ОТЛАДОЧНОГО БЛОКА
}

nettime::~nettime() {}
