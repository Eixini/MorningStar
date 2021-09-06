#ifndef INFO_H
#define INFO_H

#include <QDialog>

class info : public QDialog
{
    Q_OBJECT
public:
    explicit info(QDialog *parent = nullptr);
    ~info();

signals:

};

#endif // INFO_H
