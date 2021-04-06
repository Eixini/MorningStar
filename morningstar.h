#ifndef MORNINGSTAR_H
#define MORNINGSTAR_H

#include <QWidget>

class QPushButton;

class MorningStar : public QWidget
{
    Q_OBJECT

public:
    MorningStar(QWidget *parent = nullptr);
    ~MorningStar();

public slots:

    void showInfo(); // для создания окна с отображением информации
    void showRand(); // для создания окна с генерацией случайного числа
    void showTimer(); // для создания окна с установкой таймера
    void showNote(); // для создания окна со списком заметок
    void showNettime(); // для создания окна для получения точного времени из Интернета

private:

    QPushButton *nettime; // создание объекта кнопки для получение точного времени из интернета
    QPushButton *noteButton; // создание объекта кнопки для создания заметки
    QPushButton *timer; // создание объекта кнопки для таймера
    QPushButton *randnum; // создание объкта кнопки для виджета с генерацией случайного числа в заданном диапозоне
    QPushButton *info; // создание объекта кнопки для виджета с информацией о приложении
    QPushButton *quit; // создание объекта кнопки для выходу из приложения

};
#endif // MORNINGSTAR_H
