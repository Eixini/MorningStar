#ifndef RANDNUM_H
#define RANDNUM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>


class QNixieNumber;

class randnum : public QDialog
{
    Q_OBJECT
private:

    QVBoxLayout headVerticalLayout;
    QHBoxLayout spinboxHorizontalLayout;
    QHBoxLayout spinboxHorizontalLayoutMin;
    QHBoxLayout spinboxHorizontalLayoutMax;
    QNixieNumber *showRandnumResult;
    QLabel label_min;
    QLabel label_max;
    QSpinBox spinbox_min;
    QSpinBox spinbox_max;
    QPushButton generateRandNumButton;
    QPushButton toMainMenuButton;

    static int randnumResult;                             // Статическая переменная для хранения результатов генерации случайного числа

private slots:

    void generate();                                      // Слот для генерации случайных чисел

public:
    explicit randnum(QDialog *parent = nullptr);
    ~randnum();

public slots:


};

#endif // RANDNUM_H
