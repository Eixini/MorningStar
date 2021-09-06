#ifndef RADIO_H
#define RADIO_H

#include <QDialog>

class radio : public QDialog
{
    Q_OBJECT
public:
    explicit radio(QDialog *parent = nullptr);
    ~radio();

signals:

};

#endif // RADIO_H
