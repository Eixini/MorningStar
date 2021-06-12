#ifndef NOTE_H
#define NOTE_H

#include <QDialog>
#include <QFile>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QValidator>

#include "notemodel.h"

class QTableView;
class QHeaderView;
class QTableWidget;
class QSortFilterProxyModel;
class QTableWidgetItem;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QComboBox;
class QTextEdit;
class QLineEdit;
class QIcon;
class QSystemTrayIcon;
class QString;
class QStandardPatch;
class QDir;
class QMediaPlayer;

class note : public QDialog
{
    Q_OBJECT
public:
    explicit note(QDialog *parent = nullptr);
    ~note();

public slots:

    void noteRead();                         // Слот для проверки на существование директории и заметок в ней

private:

    QTableView *tableview;                   // Создание объекта для хранения виджетов (текстовых и голосовых заметок)
    NoteModel *notemodel;                    // Создание объекта модели для предоставления способа работы с данными
    QSortFilterProxyModel *sortmodel;         // Создание объекта для сортировки заметок

    QSystemTrayIcon *trayicon;               // Создание объекта для иконки панель задачь и показе информации

    QPushButton *toMainMenuButton;           // Кнопка для возврата в главное меню
    QPushButton *createTextNoteButton;       // Кнопка для открытия окна, где создается новая текстовая заметка
    QPushButton *createVoiceNoteButton;      // Кнопка для открытия окна, где создается новая голосовая заметка
    QPushButton *deleteNoteButton;           // Кнопка для удаления заметки

    QHBoxLayout *buttonsLayout;
    QVBoxLayout *headLayout;

    QString *nameTextNote;                   // Строка для хранения имени текстовой заметки
    QString *nameVoiceNote;                  // Строка для хранения имени голосовой заметки

    QFile audioFile;                         // Для работы с аудио файлами
    QFile textFile;                          // Для работы с текстовыми файлами

    QAudioInput *audioInput;                          // Создание объекта для потока записи с аудио
    QAudioFormat audioForm;                           // Создание объекта для установок форматов для аудио
    QAudioDeviceInfo audioDeviceInfo;                 // Создание объекта для получение инофрмации об устройстве записи

    QComboBox *noteTypeComboBox;                      // Для выбора фильтра отображения типа заметки

private slots:

    void createTextNote();                   // Слот для создания текстовой заметки
    void createVoiceNote();                  // Слот для создания голосовой заметки
    void deleteNote();                       // Слот для удаления заметки
    void generateNameForTextNote();          // Слот для генерации имени для текстовой заметки (в зависимости от текущего времени и даты), если не было введено название
    void generateNameForVoiceNote();         // Слот для генерации имени для голосовой заметки (в зависимости от текущего времени и даты)
    void writeHeader();                      // Запись заголовка в аудио-файл
    void recorderStart();                    // Слот для запуска записи
    void recorderStop();                     // Слот для окончания записи
    void handleStateChanged();               // Слот для информирвоания о состоянии записи

    void showNote(const QModelIndex & index);                     // Слот для просмотра/воспроизведения заметки

};

#endif // NOTE_H
