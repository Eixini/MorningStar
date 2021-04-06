#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include <QObject> // Q_OBJECT

// упреждающие определения классов, чтобы не подключать заголовочные файлы
// в наш заголовочный файл.
class QHBoxLayout;
class QLCDNumber;
class QLabel;
class QPushButton;
class QSpinBox;
class QTimer;
class QVBoxLayout;

class timer : public QDialog
{
    Q_OBJECT
public:
    explicit timer(QDialog *parent = nullptr);
    ~timer();

private:

    QPushButton *mainmenu; // создание объекта кнопки для возврата в главное меню
    QPushButton *setTimerButton; // создание объекта кнопки для установки таймера
    QPushButton *cancelTimerButton; // создание объекта кнопки для отмены таймера
    QPushButton *startTimerButton; // создание объекта кнопки для запуска таймера

    QSpinBox *thour; // создание объекта спинбокса для установки часов
    QSpinBox *tminut; // создание объекта спинбокса для устанвоки минут

    QLCDNumber *hourLCD; // создание объекта lcd для отображения установленного таймера (часы)
    QLCDNumber *minutLCD; // создание объекта lcd для отображения установленного таймера (минуты)

    QVBoxLayout *vbox; // Создание объекта вертикального компоновщика
    QHBoxLayout *hboxSpinbox; // Создание объекта горизонтального компоновщика
    QHBoxLayout *hboxLCD; // создание объекта горизонтального компоновщика
    QHBoxLayout *hboxLabel; // создание объекта горизонтального компоновщика

    QLabel *labmin; // Создание объекта текстовой метки для подписи lcd (минуты)
    QLabel *labhour; // Создание объекта текстовой метки для подписи lcd (часы)

    QTimer *timer_val; // Создание объекта таймера

    long minuteTomsec(long minuteVal); // функция для преобразования минут в миллисекунды
    long long hourTomsec(long hourVal); // функция для преобразования часов в миллисекнуды



private slots:

    void startTimer(); // слот для запуска таймера
    void LCDValueMin(); // Слот для установки минут
    void LCDValueHour(); // Слот для установки часов
    void cancelTimer(); // слот для отмены таймера
    void showMessage(); // Слот для показа сообщения об истечении таймера



};

#endif // TIMER_H
