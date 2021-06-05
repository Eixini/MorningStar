#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include "QNixieNumber/qnixienumber.h"

// упреждающие определения классов, чтобы не подключать заголовочные файлы
// в наш заголовочный файл.
class QHBoxLayout;
class QLCDNumber;
class QLabel;
class QPushButton;
class QSpinBox;
class QTimer;
class QVBoxLayout;
class QProgressBar;
class QSystemTrayIcon;

class timer : public QDialog
{
    Q_OBJECT
public:
    explicit timer(QDialog *parent = nullptr);
    ~timer();

private:

    unsigned int sumSec;                      // Переменная для хранения суммы секунд (часы + минуты + секунды)
    unsigned int progBarValue;                // Для увеличения прогресс бара от 0 до 100 %

    QPushButton *mainmenu;                    // создание объекта кнопки для возврата в главное меню
    QPushButton *setTimerButton;              // создание объекта кнопки для установки таймера
    QPushButton *cancelTimerButton;           // создание объекта кнопки для отмены таймера
    QPushButton *startTimerButton;            // создание объекта кнопки для запуска таймера

    QSpinBox *thour;                 // создание объекта спинбокса для установки часов
    QSpinBox *tminut;                // создание объекта спинбокса для устанвоки минут
    QSpinBox *tsecond;               // создание объекта спинбокса для установки секунд

    QNixieNumber *hourNIXIE;         // для отображения установленного таймера (часы)
    QNixieNumber *minuteNIXIE;       // для отображения установленного таймера (минуты)
    QNixieNumber *secondNIXIE;       // для отображения установленного таймера (секунды)

    QVBoxLayout *vbox;              // Создание объекта вертикального компоновщика
    QHBoxLayout *hboxSpinbox;       // Создание объекта горизонтального компоновщика
    QHBoxLayout *hboxNumber;        // создание объекта горизонтального компоновщика
    QHBoxLayout *hboxLabel;         // создание объекта горизонтального компоновщика

    QProgressBar *pbar;              // Создание объекта прогресс бара

    QTimer *timer_val;                  // Создание объекта таймера

    QSystemTrayIcon *trayicon;          // Создание объекта значка для панели задач.

    long minuteTomsec(long minuteVal);              // Метод для преобразования минут в миллисекунды
    long long hourTomsec(long hourVal);             // Метод для преобразования часов в миллисекнуды
    int secondTomsec(short secondVal);              // Метод для преобразования секунд в миллисекунды

private slots:

    void startTimer();                  // слот для запуска таймера
    void NumberValueMin();              // Слот для установки минут
    void NumberValueHour();             // Слот для установки часов
    void NumberValueSecond();           // Слот для установки секунд
    void cancelTimer();                 // слот для отмены таймера
    void updateTime();                  // Слот для обновления времени
    void showMessage();                 // Слот для показа сообщения об истечении таймера

};

#endif // TIMER_H
