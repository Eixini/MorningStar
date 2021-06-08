#include "morningstar.h"
#include "info.h"
#include "nettime.h"
#include "note.h"
#include "radio.h"
#include "randnum.h"
#include "timer.h"
#include "settings.h"
#include "textanalysis.h"

#include <QIcon>

MorningStar::MorningStar(QWidget *parent) : QDialog(parent)
{

    // ================== Configuring Components ====================

    buttonRadio.setText(tr("Radio"));
    buttonRadio.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonRadio.setIcon(QIcon(":/morningstar_resources/icons/radio_icon.png"));

    buttonNettime.setText(tr("Exact time"));
    buttonNettime.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonNettime.setIcon(QIcon(":/morningstar_resources/icons/clock_icon.png"));

    buttonNote.setText(tr("Note"));
    buttonNote.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonNote.setIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"));

    buttonTimer.setText(tr("Timer"));
    buttonTimer.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonTimer.setIcon(QIcon(":/morningstar_resources/icons/timer_icon.png"));

    buttonTextAnalysis.setText(tr("Text analysis"));
    buttonTextAnalysis.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonTextAnalysis.setIcon(QIcon(":/morningstar_resources/icons/notebook_icon.png"));

    buttonRandnum.setText(tr("Random number"));
    buttonRandnum.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonRandnum.setIcon(QIcon(":/morningstar_resources/icons/ball_icon.png"));

    buttonInfo.setText(tr("About application"));
    buttonInfo.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonInfo.setIcon(QIcon(":/morningstar_resources/icons/info_icon.png"));

    buttonSettings.setText(tr("Settings"));
    buttonSettings.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonSettings.setIcon(QIcon(":/morningstar_resources/icons/tool_icon.png"));

    buttonExit.setText(tr("Exit"));
    buttonExit.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    buttonExit.setIcon(QIcon(":/morningstar_resources/icons/door_icon.png"));

    // ++++++++++++++++++ Setting up connections ++++++++++++++++++++

    connect(&buttonRadio, &QPushButton::clicked, this, &MorningStar::showRadio);
    connect(&buttonNettime, &QPushButton::clicked, this, &MorningStar::showNettime);
    connect(&buttonNote, &QPushButton::clicked, this, &MorningStar::showNote);
    connect(&buttonTimer, &QPushButton::clicked, this, &MorningStar::showTimer);
    connect(&buttonTextAnalysis, &QPushButton::clicked, this, &MorningStar::showTextAnalysis);
    connect(&buttonRandnum, &QPushButton::clicked, this, &MorningStar::showRandnum);
    connect(&buttonInfo, &QPushButton::clicked, this, &MorningStar::showInfo);
    connect(&buttonSettings, &QPushButton::clicked, this, &MorningStar::showSettings);
    connect(&buttonExit, &QPushButton::clicked, qApp, &QApplication::quit);

    // ~~~~~~~~~~~~~~~~~~ Layout customization ~~~~~~~~~~~~~~~~~~~~~~

    vbox.addWidget(&buttonRadio);
    vbox.addWidget(&buttonNettime);
    vbox.addWidget(&buttonNote);
    vbox.addWidget(&buttonTimer);
    vbox.addWidget(&buttonTextAnalysis);
    vbox.addWidget(&buttonRandnum);
    vbox.addWidget(&buttonInfo);
    vbox.addWidget(&buttonSettings);
    vbox.addWidget(&buttonExit);

    setLayout(&vbox);           // Setting the linker as the main window for a window

}

void MorningStar::showRadio()
{
    class radio radioWin;

    radioWin.setModal(true);
    radioWin.setWindowTitle(tr("Radio"));
    radioWin.setWindowIcon(QIcon(":/morningstar_resources/icons/radio_icon.png"));

    radioWin.exec();
}

void MorningStar::showNettime()
{
    class nettime nettimeWin;

    nettimeWin.setModal(true);
    nettimeWin.setWindowTitle(tr("Exact time"));
    nettimeWin.setWindowIcon(QIcon(":/morningstar_resources/icons/clock_icon.png"));

    nettimeWin.exec();
}

void MorningStar::showNote()
{
    class note noteWin;

    noteWin.setModal(true);
    noteWin.setWindowTitle(tr("Note"));
    noteWin.setWindowIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"));
    noteWin.noteRead();

    noteWin.exec();
}
void MorningStar::showTimer()
{
    class timer timerWin;

    timerWin.setModal(true);
    timerWin.setWindowTitle(tr("Timer"));
    timerWin.setWindowIcon(QIcon(":/morningstar_resources/icons/timer_icon.png"));
    timerWin.setMinimumSize(400,370);

    timerWin.exec();
}

void MorningStar::showTextAnalysis()
{
    class textanalysis textanalysisWin;

    textanalysisWin.setModal(true);
    textanalysisWin.setWindowTitle(tr("Text analysis"));
    textanalysisWin.setWindowIcon(QIcon(":/morningstar_resources/icons/notebook_icon.png"));

    textanalysisWin.exec();
}

void MorningStar::showRandnum()
{
    class randnum randnumWin;

    randnumWin.setModal(true);
    randnumWin.setWindowTitle(tr("Random number"));
    randnumWin.setWindowIcon(QIcon(":/morningstar_resources/icons/ball_icon.png"));

    randnumWin.exec();
}

void MorningStar::showInfo()
{
    class info infoWin;

    infoWin.setModal(true);
    infoWin.setWindowTitle(tr("About application"));
    infoWin.setWindowIcon(QIcon(":/morningstar_resources/icons/info_icon.png"));

    infoWin.exec();
}
void MorningStar::showSettings()
{
    class settings settingsWin;

    settingsWin.setModal(true);
    settingsWin.setWindowTitle(tr("Settings"));
    settingsWin.setWindowIcon(QIcon(":/morningstar_resources/icons/tool_icon.png"));

    settingsWin.exec();
}

MorningStar::~MorningStar() { }
