#ifndef NETTIME_H
#define NETTIME_H

#include <QDialog>

class nettime : public QDialog
{
    Q_OBJECT
public:
    explicit nettime(QDialog *parent = nullptr);
    ~nettime();

signals:

};

#endif // NETTIME_H
