#ifndef TEXTANALYSIS_H
#define TEXTANALYSIS_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QString>

class QSystemTrayIcon;

class textanalysis : public QDialog
{
    Q_OBJECT
public:
    explicit textanalysis(QDialog *parent = nullptr);
    ~textanalysis();


private:

    QFileDialog fdialog;            // Создание объекта для работы с файловым диалоговыми окнами
    QPushButton openFileButton;     // Создание объекта кнопки для открытия файлового диалогового окна
    QPushButton textFieldButton;    // СОздание объекта кнопки для обработки текста с поля ввода
    QPushButton mainmenuButton;     // Создание объекта кнопки для возврата в главное меню
    QTextEdit textenter;            // Создание объекта для ввода текста

    QHBoxLayout hbox;               // Создание объекта горизонтальной компоновки (главной)
    QVBoxLayout vbox;               // Создание объекта вертикальной компоновки
    QFormLayout formlayout;         // Создание объекта компоновки для тектовой метки - виджета

    QString fileName;               // Объект строкового типа для сохранения имя выбранного файла
    QString dir;                    // Объект строкового типа для хранения директории

    QSystemTrayIcon *trayiconInfo;  // Объект для вывода информации на панеле задач

    // +++++++++++++++++++++++++++++++++ ДЛЯ ПОДСЧЕТА КОЛИЧЕСТВО ЕДЕНИЦ ТЕКСТА ++++++++++++++++++++++++++++

    int symbols_;               // Для хранения числа символов
    int space_;                 // Для хранения числа пробелов
    int numeral_;               // Для хранения числа цифр
    int letter_;                // Для хранения числа букв
    int punct_;                 // Для хранения числа знаков пунктуации
    int word_;                  // Для хранения количества слов

    QString readstring;         // Для хранения текса для обработки

    // Для установки значений в виджет текстовой метки

    QLabel lsymbols;            // Для установки значения числа символов
    QLabel lspace;              // Для установки значения числа пробелов
    QLabel lnumeral;            // Для установки значения числа цифр
    QLabel lletter;             // Для установки значения числа букв
    QLabel lpunct;              // Для установки значения числа знаков пунктуации
    QLabel lword;               // Для установки значения количества слов


    int wordCounter(QString &str) const;   // Счетчик слов

private slots:

    void fileDialog();                           // Слот для открытие файла и обработки информации
    void textField();                            // Слот для обработки информации и поля ввода
    void textProcessing(QString &str);           // Метод для обработки переданного символа

};

#endif // TEXTANALYSIS_H
