#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class settings : public QDialog
{
    Q_OBJECT
public:
    explicit settings(QDialog *parent = nullptr);
    ~settings();

signals:

};

#endif // SETTINGS_H
