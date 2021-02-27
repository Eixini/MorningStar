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

private slots:

    void copyPath(); // Слот для копирования содержимого строки для указания пути

private:

    QPushButton *mainmenu; // Создание объекта кнопки для возвращения в главное меню
    QPushButton *okButton; // Создание объекта кнопки дляприменения файлового пути
    QLabel *exampleFolder; // Создание объекта текстовой метки для указания пути
    QLabel *selectLabel; // Создание объекта метки для строчки с текущем расположением файлов
    QLineEdit *selectPath; // Создание объекта для сохранения пути

    QVBoxLayout *vbox; // Создание объекта компоновки
    QFormLayout *formbox; // Создание объекта компоновки
    QHBoxLayout *sbox; // Создание объекта компоновки
    QHBoxLayout *buttonBox; // Создание объекта компоновщика для размещения кнопок

};

#endif // SETTINGS_H
