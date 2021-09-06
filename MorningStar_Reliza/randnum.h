#ifndef RANDNUM_H
#define RANDNUM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <array>

class QSystemTrayIcon;
class QNixieNumber;
class QTimer;

class randnum : public QDialog
{
    Q_OBJECT
private:

    QVBoxLayout headVerticalLayout;
    QHBoxLayout spinboxHorizontalLayout;
    QHBoxLayout spinboxHorizontalLayoutMin;
    QHBoxLayout spinboxHorizontalLayoutMax;
    QHBoxLayout nixieDisplayLayout;

    QTimer *timer;

    static const int SIZE_ARRAY = 10;

    std::array<QNixieNumber*, SIZE_ARRAY> NixieDisplay;

    QLabel label_min;
    QLabel label_max;
    QSpinBox spinbox_min;
    QSpinBox spinbox_max;
    QPushButton generateRandNumButton;
    QPushButton toMainMenuButton;   
    QSystemTrayIcon *trayicon;          // Создание объекта значка для панели задач

    static int randnumResult;                             // Статическая переменная для хранения результатов генерации случайного числа
    QVector <int> splitRandnumResult;                     // Вектор для хранения раздробленного числа
    int interResult;                                      // Переменная для хранения промежуточного результата

private slots:

    void generate();                                      // Слот для генерации случайных чисел
    int split(int number);                                // Дробление числа

public:
    explicit randnum(QDialog *parent = nullptr);
    ~randnum();

public slots:


};

#endif // RANDNUM_H
