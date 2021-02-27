#ifndef NETTIME_H
#define NETTIME_H

#include <QWidget>
#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QGridLayout>
#include <QLabel>
#include <QTime>

class nettime : public QDialog
{
    Q_OBJECT
public:
    explicit nettime(QDialog *parent = nullptr);
    ~nettime();

private:

    QPushButton *mainmenu; // Создание объекта кнопки для возврата в главное меню
    QPushButton *requestButton; // Создание объекта кнопки для запроса точного времени из интернета

    QComboBox *nettimeList; // Создание объекта выпадающего списка городов (часовых поясов)

    // Создание объектов LCD для отображения часов,минут и секунд
    QLCDNumber *hLCD;
    QLCDNumber *mLCD;
    QLCDNumber *sLCD;

    // Создание объектов текстовых меток для подписи LCD
    QLabel *hlabel;
    QLabel *mlabel;
    QLabel *slabel;

    QLabel *labCityText; // Создание объекта тектовой метки для подписи выбираемого города
    QLabel *selectCity; // Создание объекта текстовой метки для выбранного города

    QGridLayout *grid; // Создание объекта сетчетого компоновщика
    QHBoxLayout *hbox; // Создание объекта горизонтального компоновщика
    QVBoxLayout *vbox; // Создание объекта вертикального компоновщика
    QVBoxLayout *vboxLab; // Создание объекта вертикального компоновщика

private slots:

    void TimeRequest(); // Слот для запроса времени из интернета

};

#endif // NETTIME_H
