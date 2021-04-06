#ifndef RANDNUM_H
#define RANDNUM_H

#include <QDialog>
#include <QObject>

class QHBoxLayout;
class QLabel;
class QPushButton;
class QSpinBox;
class QVBoxLayout;

class randnum : public QDialog
{
    Q_OBJECT
public:
    explicit randnum(QDialog *parent = nullptr);
    ~randnum();

private:

    QPushButton *mainmenu; // Создание объекта кнопки для возврата в главное окно
    QPushButton *generate; // Создание объекта кнопки для генерации числа

    QLabel *shownum; // Создание объекта текстовой метки для отображения числа
    QLabel *errorRange; // создание объекта текста отображения сообщения ошибки
    QSpinBox *smin; // Создание объекта для записи минимального числа
    QSpinBox *smax; // Создание объекта для записи максимального числа

    QVBoxLayout *vbox; // создание объекта вертикального компоновщика
    QHBoxLayout *hbox; // создание объекта горизонтального компоновщика
    QVBoxLayout *vrange; // создание объекта вертикального компоновщика для отображения числа и настрйоки диапазона

private slots:

    void ShowResult();

};

#endif // RANDNUM_H
