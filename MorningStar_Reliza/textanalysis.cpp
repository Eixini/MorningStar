#include "textanalysis.h"

#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QChar>
#include <QStandardPaths>
#include <QFile>

textanalysis::textanalysis(QDialog *parent) : QDialog(parent)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ~~~~~~~~~~~~~~~~~~~~~~~~
    {
        trayiconInfo = new QSystemTrayIcon(QIcon(":/morningstar_resources/icons/notebook_icon.png"), this);
    }

    // ----------------------------  Настройка объектов --------------------------
    {
    openFileButton.setText("Открыть документ");
    textFieldButton.setText("Анализ текста с поля");
    mainmenuButton.setText("В меню");

    dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    fdialog.setNameFilter(".txt");
    fdialog.setFileMode(QFileDialog::ExistingFile);
    }

    // ++++++++++++++++++++++ Управление сигналами/слотами +++++++++++++++++++++++
    {
    connect(&mainmenuButton, &QPushButton::clicked, this, &QDialog::accept);             // Возврат в главное меню
    connect(&openFileButton, &QPushButton::clicked, this, &textanalysis::fileDialog);    // Нажатие кнопки для открыие файлового диалогово окна
    connect(&textFieldButton, &QPushButton::clicked, this, &textanalysis::textField);    // Нажатие кнопки для обработки текста из поля для ввода
    }

    // ======================== Управление компоновкой ===========================
    {
    formlayout.addRow("Символы:  ", &lsymbols);
    formlayout.addRow("Буквы:    ", &lletter);
    formlayout.addRow("Цифры:    ", &lnumeral);
    formlayout.addRow("Знаки:    ", &lpunct);
    formlayout.addRow("Пробелы:  ", &lspace);
    formlayout.addRow("Слов:     ", &lword);

    vbox.addWidget(&openFileButton);
    vbox.addWidget(&textFieldButton);
    vbox.addStretch(1);
    vbox.addLayout(&formlayout);
    vbox.addStretch(1);
    vbox.addWidget(&mainmenuButton);

    hbox.addWidget(&textenter);
    hbox.addLayout(&vbox);

    setLayout(&hbox); // Установка компоновщика в качестве основного
    }

}

void textanalysis::fileDialog()
{
    // Слот для открытие файла и обработки информации

    fileName = QFileDialog::getOpenFileName(this,"Открыть текстовый файл", dir, "Текстовые файлы(*.txt)");

    QFile file(fileName);
    file.open(QIODevice::ReadOnly); // Открытие файла только для чтения

    if(file.isOpen())
    {
        trayiconInfo->setVisible(true);
        trayiconInfo->showMessage(tr("Анализ текста"),tr("Файл успешно открыт!"));

        while(!file.atEnd()) // Пока не достигнут конец файла
        {
            readstring = file.readAll();
            textProcessing(readstring);
        }
    }
    else
    {
        trayiconInfo->setVisible(true);
        trayiconInfo->showMessage(tr("Анализ текста"),tr("Файл не открыт!"));
    }

    file.close();                                                            // Закрытие файла после работы с ним
}

void textanalysis::textField()
{
   // Слот для обработки информации и поля ввода

   readstring = textenter.toPlainText();

   textProcessing(readstring);
}

void textanalysis::textProcessing(QString &str)
{
    symbols_ = 0;
    letter_ = 0;
    numeral_ = 0;
    space_ = 0;
    punct_ = 0;
    word_ = 0;


    int i = 0; // Для итерации

        while(i < readstring.size())
        {
            if(readstring.at(i).isLetter())
                letter_++;

            if(readstring.at(i).isSpace())
                space_++;

            if(readstring.at(i).isNumber())
                numeral_++;

            if(readstring.at(i).isPunct())
                punct_++;
            i++;
            symbols_++;
        }

        word_ = wordCounter(readstring);

        // Установка значений в объекты QLabel
        lsymbols.setText(QString::number(symbols_));
        lletter.setText(QString::number(letter_));
        lnumeral.setText(QString::number(numeral_));
        lspace.setText(QString::number(space_));
        lpunct.setText(QString::number(punct_));
        lword.setText(QString::number(word_));

}

int textanalysis::wordCounter(QString &str) const
{
    int word = 0;                // Подсчет количества слов

    int i = 0;                   // Для итерации
    int continuity = 0;          // Счетчик непрерывности набора букв

    while(i < readstring.size())
    {
         if(readstring.at(i).isLetter())
          continuity++;

         if(readstring.at(i).isSpace() && (continuity > 0))
         {
             word++;
             continuity = 0;
         }

         i++;
    }
    if(continuity > 0)
        word++;

    return word;
}

textanalysis::~textanalysis() {}
