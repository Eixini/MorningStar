#ifndef NOTE_H
#define NOTE_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QLineEdit>
#include <QFormLayout>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include "morningstar.h"

class note : public QDialog
{
    Q_OBJECT
public:
    explicit note(QDialog *parent = nullptr);
    ~note();

    QListWidget *notelist; // Создание объекта списка заметок

private:

    QPushButton *mainmenu; // Создание объекта кнопки для возврата в главное меню
    QPushButton *addButton; // Создание объекта кнопки для добавления новой заметки
    QPushButton *editButton; // Создание объекта кнопки для редактирования существующей заметки
    QPushButton *removeButton; // Создание объекта кнопки для удаления заметки

    QVBoxLayout *vbox; // Создание объекта вертикального компоновщика
    QHBoxLayout *hbox; // Создание объекта горизонтального компоновщика

    QFile *noteFile; // Создание объект для работы с файлом заметок


    // --------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ СОЗДАНИЯ ЗАМЕТОК ______________________________

    //QDialog *addNoteWin; // Создание объекта диалогового окна

    // --------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ РЕДАКТИРОВАНИЯ ЗАМЕТОК -----------------------

    QDialog *editNoteWin; // Создание объекта диалогового окна

    QLineEdit *editTitleNote; // Создание объекта для редактирования названия заметки

    QVBoxLayout *editNoteVBox; // Создание объекта компоновщика
    QFormLayout *formLineEdit; // Создание объекта компоновщика для подписи текста
    QHBoxLayout *hboxForEditButtons; // создание объекта горизонтального компоновщика

    QPushButton *editAccept; // Создание объекта кнопки для принятия изменений
    QPushButton *editCancel; // Создание объекта кнопки для отмены изменений

    QString *noteName; // Создание указателя на переменную типа стринг

    // --------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ ПОКАЗА ЗАМЕТОК --------------------------------

    QDialog *showNoteWin; // Создание объекта диалогового окна

private slots:

    void addNote(); // Слот для добавления новой заметки
    void removeNote(); // слот для удаления заметки
    void editNote(); // Слот для редактирования заметки
    void setNoteNameText();

public slots:

    void note_read(); // Создание слота для считывания заметок из файла

};

#endif // NOTE_H
