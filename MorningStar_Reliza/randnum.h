#ifndef RANDNUM_H
#define RANDNUM_H

#include <QDialog>

class randnum : public QDialog
{
    Q_OBJECT
public:
    explicit randnum(QDialog *parent = nullptr);
    ~randnum();

signals:


};

#endif // RANDNUM_H
