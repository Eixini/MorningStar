#ifndef MORNINGSTAR_H
#define MORNINGSTAR_H

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class MorningStar : public QDialog
{
    Q_OBJECT

public:
    MorningStar(QWidget *parent = nullptr);
    ~MorningStar();

private:

    // Buttons for calling windows

    QPushButton buttonRadio;
    QPushButton buttonNettime;
    QPushButton buttonNote;
    QPushButton buttonTimer;
    QPushButton buttonTextAnalysis;
    QPushButton buttonRandnum;
    QPushButton buttonInfo;
    QPushButton buttonSettings;
    QPushButton buttonExit;

    QVBoxLayout vbox;           // To layout buttons in the main window



private slots:

    // Slots for calling windows

    void showRadio();            // Configuring and calling a window for Radio from the Internet
    void showNettime();          // Configuring and calling a window for Request to get the exact time from the Internet
    void showNote();             // Configuring and calling a window for Working with notes
    void showTimer();            // Configuring and calling a window for Timer setting
    void showTextAnalysis();     // Configuring and calling a window for Symbolic text analysis
    void showRandnum();          // Configuring and calling a window for Generating a random number
    void showInfo();             // Configuring and calling a window for Show application and system information
    void showSettings();         // Configuring and calling a window for Settings

};
#endif // MORNINGSTAR_H
