#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QDialog>
#include <QApplication>
#include <QWindow>
#include <QIcon>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QAbstractButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSysInfo>
#include <QPixmap>

class info : public QDialog
{
    Q_OBJECT

public:

    info(QDialog *parent = nullptr);
    ~info();

private:

    QPushButton *mainmenu; // Создание объекта кнопки для возврата в главное окно
    QLabel *infotext; // Создание объекта для текстового описания
    QLabel *infodev; // Создание объекта для текстового описания
    QLabel *labkernel; // Создание объекта метки для версии ядра
    QLabel *labtypeos; // Создание объекта метки для типа ОС
    QLabel *info_image; // Для установки изображения

};

#endif // INFO_H
