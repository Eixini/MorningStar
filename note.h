#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QFile>

#include "morningstar.h"

#include <QString>
#include <QTextStream>

class note : public QDialog
{
    Q_OBJECT
public:
    explicit note(QDialog *parent = nullptr);
    ~note();

private:

    QPushButton *mainmenu; // Создание объекта кнопки для возврата в главное меню
    QPushButton *addButton; // Создание объекта кнопки для добавления новой заметки
    QPushButton *editButton; // Создание объекта кнопки для редактирования существующей заметки
    QPushButton *removeButton; // Создание объекта кнопки для удаления заметки

    QVBoxLayout *vbox; // Создание объекта вертикального компоновщика
    QHBoxLayout *hbox; // Создание объекта горизонтального компоновщика

    QListWidget *notelist; // Создание объекта списка заметок

    //---------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ РЕДАКТИРОВАНИЯ ЗАМЕТОК ------------------------
    QDialog *editNoteWin; // Создание объекта диалогового окна
    QLineEdit *editTitleNote; // Создание объекта для редактирования названия заметки
    QTextEdit *editTextNote; // Создание объекта для редактирвоания текста

    QVBoxLayout *editNoteVBox; // Создание объекта компоновщика
    QFormLayout *formLineEdit; // Создание объекта компоновщика для подписи текста
    QHBoxLayout *hboxForEditButtons; // создание объекта горизонтального компоновщика

    QPushButton *editAccept; // Создание объекта кнопки для принятия изменений
    QPushButton *editApply; // СОздание объекта кнопки для принятия изменения
    QPushButton *editCancel; // Создание объекта кнопки для отмены изменений

    QLabel *LabelEditTextNote; // Создание объекта текстовой метки для текстовой области

    QString *noteName; // Создание указателя на переменную типа стринг

    // --------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ СОЗДАНИЯ ЗАМЕТОК ______________________________

    //QDialog *addNoteWin; // Создание объекта диалогового окна

    // --------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ ПОКАЗА ЗАМЕТОК --------------------------------

    QDialog *showNoteWin; // Создание объекта диалогового окна

private slots:

    void addNote(); // Слот для добавления новой заметки
    void removeNote(); // слот для удаления заметки
    void editNote(); // Слот для редактирования заметки
    void showNote(); // Слот для показа заметки

    void setNoteNameText(); // Слот для копирования текста из QLineEdit в переменную типа стринг


};

#endif // NOTE_H
