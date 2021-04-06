#ifndef NETTIME_H
#define NETTIME_H

#include <QDialog>

#include <QDateTime>
#include <QJsonDocument>

#include <QString>
#include <QObject> // Q_OBJECT

// упреждающие определения классов, чтобы не подключать заголовочные файлы
// в наш заголовочный файл.
class QComboBox;
class QGridLayout;
class QHBoxLayout;
class QLCDNumber;
class QLabel;
class QNetworkAccessManager;
class QNetworkReply;
class QVBoxLayout;

class nettime : public QDialog
{
    Q_OBJECT
public:
    explicit nettime(QDialog *parent = nullptr);
    ~nettime();

private:

    static const int SITIES = 11; // Константа для хранения количества часовых поясов

    QPushButton *mainmenu; // Создание объекта кнопки для возврата в главное меню
    QPushButton *requestButton; // Создание объекта кнопки для запроса точного времени из интернета

    QComboBox *nettimeList; // Создание объекта выпадающего списка городов (часовых поясов)

    QNetworkAccessManager *net; // СОздание объкт класса для работы с сетью

    QTime time; // Объект для хранения локальной копии полученного из сети времени
    QTimer *timer; // Объект таймера для обновления показаний LCD
    QDateTime date; // Объект для хранение локальной копии Даты. времени
    QJsonDocument jsonData; // Объект для хранения полного полученного JSON документа

    // Создание объектов LCD для отображения часов,минут и секунд
    QLCDNumber *hLCD;
    QLCDNumber *mLCD;
    QLCDNumber *sLCD;

    // Создание объектов текстовых меток для подписи LCD
    QLabel *hlabel;
    QLabel *mlabel;
    QLabel *slabel;

    QLabel *labCityText; // Создание объекта тектовой метки для подписи выбираемого города

    QGridLayout *grid; // Создание объекта сетчетого компоновщика
    QHBoxLayout *hbox; // Создание объекта горизонтального компоновщика
    QVBoxLayout *vbox; // Создание объекта вертикального компоновщика
    QVBoxLayout *vboxLab; // Создание объекта вертикального компоновщика

    QString cityTime; // Для хранения ссылки на запрос данных
    QString dataTime; // Для хранения полученных данных
    QString timeValue; // Для хранение извлеченных данных из JSON документа

    QString city[SITIES] = {
                            "http://worldtimeapi.org/api/timezone/Europe/Kaliningrad",
                            "http://worldtimeapi.org/api/timezone/Europe/Moscow",
                            "http://worldtimeapi.org/api/timezone/Europe/Samara",
                            "http://worldtimeapi.org/api/timezone/Asia/Yekaterinburg",
                            "http://worldtimeapi.org/api/timezone/Asia/Omsk",
                            "http://worldtimeapi.org/api/timezone/Asia/Novosibirsk",
                            "http://worldtimeapi.org/api/timezone/Asia/Irkutsk",
                            "http://worldtimeapi.org/api/timezone/Asia/Yakutsk",
                            "http://worldtimeapi.org/api/timezone/Asia/Vladivostok",
                            "http://worldtimeapi.org/api/timezone/Asia/Sakhalin",
                            "http://worldtimeapi.org/api/timezone/Asia/Anadyr"
                             };
;

private slots:

    void TimeRequest(); // Слот для запроса времени из интернета
    void onFinished(QNetworkReply *reply); // Слот для обработки полученных результатов
    void time_update(); // Слот для обновления показаний времени

};

#endif // NETTIME_H
