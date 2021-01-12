#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>

#include "morningstar.h"

class settings : public QDialog
{
    Q_OBJECT
public:
    explicit settings(QDialog *parent = nullptr);
    ~settings();

    QLineEdit *folderLine; // создание объекта для хранения пути для текстовых файлов

public slots:



private slots:


private:

    QPushButton *mainmenu; // Создание объекта кнопки для возвращения в главное меню
    QLabel *exampleFolder; // СОздание объекта текстовой метки для указания пути

    QVBoxLayout *vbox; // Создание объекта компоновки
    QFormLayout *formbox; // Создание объекта компоновки

};

#endif // SETTINGS_H
