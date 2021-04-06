#ifndef NOTE_H
#define NOTE_H

#include <QDialog>
#include <QObject>

class QFile;
class QHBoxLayout;
class QFormLayout;
class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;
class QVBoxLayout;

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

    // --------------------- ДИАЛОГОВОЕ ОКНО ДЛЯ РЕДАКТИРОВАНИЯ ЗАМЕТОК -----------------------

    QDialog *editNoteWin; // Создание объекта диалогового окна
    QLineEdit *editTitleNote; // Создание объекта для редактирования названия заметки
    QLabel *hint; // Создание объекта для отображения подсказки

    QVBoxLayout *editNoteVBox; // Создание объекта компоновщика
    QFormLayout *formLineEdit; // Создание объекта компоновщика для подписи текста

private slots:

    void addNote(); // Слот для добавления новой заметки
    void removeNote(); // слот для удаления заметки
    void editNote(); // Слот для редактирования заметки
    void setNoteNameText();
    void saveNote(); // слот для сохранение изменений в файл перед закрытием окна заметок

public slots:

    void note_read(); // Создание слота для считывания заметок из файла

};

#endif // NOTE_H
