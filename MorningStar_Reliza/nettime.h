#ifndef NETTIME_H
#define NETTIME_H

#include <QDialog>
#include <QString>
#include <string>

class QNetworkAccessManager;
class QPushButton;
class QLineEdit;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QCompleter;
class QNixieNumber;
class QSystemTrayIcon;
class QTime;
class QUdpSocket;
class QHostInfo;
class QHostAddress;
class QStandardPaths;

class nettime : public QDialog
{
    Q_OBJECT


public:
    explicit nettime(QDialog *parent = nullptr);
    ~nettime();

private:

    static constexpr long NTP_TIMESTAMP_DELTA{2208988800ull};       // Delta between epoch time and ntp time

    QNixieNumber *hoursDisplay;
    QNixieNumber *minutesDisplay;
    QNixieNumber *secondsDisplay;

    QVBoxLayout *headLayout;
    QHBoxLayout *displaysLayout;
    QHBoxLayout *selectCity;
    QHBoxLayout *enterLineLayout;
    QHBoxLayout *buttonsLayout;

    QLineEdit *enterCityLine;
    QCompleter *completer;

    QPushButton *toMainMenuButton;
    QPushButton *requestTimeButton;

    QLabel *labelSelectCity;
    QLabel *labelCurrentSelectCity;

    QString pathDataTZ_DB;

public slots:

    void request_time();
    void tz_database();

private slots:

};

#endif // NETTIME_H
