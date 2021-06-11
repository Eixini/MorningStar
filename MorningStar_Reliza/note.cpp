#include "note.h"

#include <qendian.h>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QIcon>
#include <QLineEdit>
#include <QTextEdit>
#include <QSystemTrayIcon>
#include <QString>
#include <QStandardPaths>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QModelIndex>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMediaPlayer>
#include <QUrl>
#include <QSlider>
#include <QLabel>

#include <QModelIndexList>
#include <QItemSelectionModel>

/*     Вопросы, требующие внимания:

    - реализовать прослушивание аудио заметки;
    - добавить сортировку по столбцам;
    - добавить ввод имени при создание голосовой заметки
    - при просмотре текстовой заметки возможность редактировать содержимое и имя заметки(файла)

    * (?) Возможно или нет, для 1 стоблца представления интерпретировать тип заметки (txt / wav ) в соответсвующие иконки;

*/

// ::::::::::::::::::::::::::::::::::::::::::::: Заголовки для WAV-файла ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
struct RIFFHeader
{
    char    chunkId[4];         // Символы "RIFF" в ASCII-кодировке, начало RIFF цепочки
    quint32 chunkSize;          // Оставшийся размер RIFF цепочки (без chunkId и chunkSize)
    char    format[4];          // Символы "WAVE" в ASCII-кодировке
};

struct WAVEHeader
{
    char    subchunk1Id[4];     // Символы "fmt" в ASCII-кодировке
    quint32 subchunk1Size;      // 16 байт для формата PCM, размер оставшейся подцепочки (без subchunk1Id и subchunk1Size)
    quint16 audioFormat;        // Аудио формат, для PCM = 1 (линейное квантование). Отличное от 1 - некоторый формат сжатия
    quint16 numChannels;        // Количество каналов (1 - Моно, 2 - Стерео и т.д)
    quint32 sampleRate;         // Частота дискретизации (например 8000 Гц, 441000 Гц и т.д)
    quint32 byteRate;           // Количество байт, переданных за секунду воспроизведения
    quint16 blockAlign;         // Количество байт для одного sample
    quint16 bitsPerSample;      // Количество бит в sample (глубина или точность звучания, например 8 бит, 16 бит и т.д)
};

struct DATAHeader
{
    char    subchank2Id[4];     // Символы "data" в ASCII-кодировке
    quint32 subchunk2Size;      // Количество байт в области данных
};

note::note(QDialog *parent) : QDialog(parent)
{
    // ::::::::::::::::::::::::::::::::::::::::: ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ :::::::::::::::::::::::::::::::::::::::::
    {
    createTextNoteButton    = new QPushButton(tr("Add new Text note"), this);          // Кнопка для создания текстовой заметки
    createVoiceNoteButton   = new QPushButton(tr("Add new Voice Note"), this);         // Кнопка для создания голосовой заметки
    deleteNoteButton        = new QPushButton(tr("Delete note"), this);                // Кнопка для удаления заметки
    toMainMenuButton        = new QPushButton(tr("Main Menu"), this);                  // Кнопка для возврата в главное меню

    trayicon        = new QSystemTrayIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"), this); // Создание объекта для уведомлений из панели задач

    buttonsLayout = new QHBoxLayout();                    // Горизонтальный компоновщик, в котором будут объекты (включая другие компоновщики)
    headLayout    = new QVBoxLayout(this);                // Вертикальный компоновщик для кнопок

    nameVoiceNote   = new QString("");                    // Строка для хранения имени голосовой заметки
    nameTextNote    = new QString("");                    // Строка для хранения имени текстовой заметки

    tableview        = new QTableView(this);              // Инициализация представления
    notemodel        = new NoteModel(this);               // Инициализация модели

    }
    // +++++++++++++++++++++++++++++++++++++++++++ НАСТРОЙКА ОБЪЕКТОВ +++++++++++++++++++++++++++++++++++++++++++
    {
        createTextNoteButton->setIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"));
        createVoiceNoteButton->setIcon(QIcon(":/morningstar_resources/icons/microphone_icon.png"));
        deleteNoteButton->setIcon(QIcon(":/morningstar_resources/icons/x_icon.png"));
        toMainMenuButton->setIcon(QIcon(":/morningstar_resources/icons/ms_icon.png"));

        tableview->setModel(notemodel);
        tableview->setCornerButtonEnabled(false);                                 // Выключить кнопку для выделения всех элементов
        tableview->horizontalHeader()->setStretchLastSection(true);               // Убрать белое пространство после последнего столбца
        tableview->setShowGrid(false);                                            // Скрыть показ сетки
        tableview->verticalHeader()->hide();
        tableview->setColumnWidth(0,70);
        tableview->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        tableview->resizeColumnToContents(2);
        tableview->setSelectionMode(QAbstractItemView::SingleSelection);
        tableview->setSelectionBehavior(QAbstractItemView::SelectRows);           // Установка поведения - при выборе ячейки, выбирается вся строка
        tableview->setSortingEnabled(true);
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ СОЗДАНИЕ СОЕДИНЕНИЙ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
    connect(toMainMenuButton, &QPushButton::clicked, this, &QDialog::accept);            // Возврат в главное меню
    connect(createTextNoteButton, &QPushButton::clicked, this, &note::createTextNote);   // Вызов окна для создания текстовой заметки
    connect(createVoiceNoteButton, &QPushButton::clicked, this, &note::createVoiceNote); // Вызов окна для создания голосовой заметки
    connect(deleteNoteButton, &QPushButton::clicked, this, &note::deleteNote);           // Удаление заметки
    connect(tableview, &QTableView::doubleClicked, this, &note::showNote);
    }
    // ***************************************** УПРАВЛЕНИЕ КОМПОНОВКОЙ *****************************************
    {
    buttonsLayout->addWidget(createTextNoteButton);
    buttonsLayout->addWidget(createVoiceNoteButton);
    buttonsLayout->addWidget(deleteNoteButton);
    buttonsLayout->addWidget(toMainMenuButton);

    headLayout->addLayout(buttonsLayout);
    headLayout->addWidget(tableview);

    setLayout(headLayout);                                             // Установка компоновщика в качестве оснвоного
    }
}

void note::createTextNote()
{  // Слот для создания текстовой заметки

    /* -------------------------------------------- СОЗДАНИЕ ОБЪЕКТОВ ОКНА ТЕКСТОВЫХ ЗАМЕТОК ---------------------------------------- */
    QDialog *textNoteWindow = new QDialog();                // Создание диалогового окна

    textNoteWindow->setWindowTitle(tr("Create new Text note"));
    textNoteWindow->setWindowIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"));

    QPushButton saveButtun(tr("Save"), textNoteWindow);                          // Кнопка для принятия установки изменения
    QPushButton cancelButton(tr("Cancel"), textNoteWindow);                      // Кнопка для отмены создания заметки

    QVBoxLayout textNoteVBoxLayout(textNoteWindow);                              // Компоновщик для размещения всех элементов данного окна
    QHBoxLayout textNoteLayoutButtons;                                           // Компоновщик для кнопок
    QFormLayout textTitleFormLayout;                                             // Компоновщик с текстовой меткой

    QLineEdit textNoteTitle(textNoteWindow);                                     // Поле ввода для названия текстовой заметки
    QTextEdit enterTextNote(textNoteWindow);                                     // Поле для воода текстовой заметки

    QRegExp regexp("([a-zA-Zа-яА-Я0-9-_.]){255}");                               // Для ограничения по вводимым символам
    QRegExpValidator REvalidator(regexp);

    /* :::::::::::::::::::::::::::::::::::::::::::::::::::::: НАСТРОЙКА ФУНКЦИОНАЛА ::::::::::::::::::::::::::::::::::::::::::::::::: */

    textNoteTitle.setPlaceholderText(tr("Допустимые символы: буквы (Lat, Cyr), цифры, тире, нижнее подчеркивание"));   // Установка текста заполнителя
    enterTextNote.setPlaceholderText(tr("Введите текст заметки..."));

    textNoteTitle.setValidator(&REvalidator);

    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ ПОДКЛЮЧЕНИЕ К СИГНАЛАМ ++++++++++++++++++++++++++++++++++++++++++++++++ */
    connect(&cancelButton, &QPushButton::clicked, textNoteWindow, &QDialog::close);
    connect(&saveButtun, &QPushButton::clicked, textNoteWindow, [&]()
    {
      if(textNoteTitle.text() != "")
      {
          QString textNoteLoc = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza" + "/TextNote";
          *nameTextNote = textNoteLoc + "/" + textNoteTitle.text() + ".txt";      // Установка названия для файла из поля для ввода
      }
      else
          generateNameForTextNote();

      textFile.setFileName(*nameTextNote);                                        // Создание текстового файла
      textFile.open(QIODevice::WriteOnly);                                        // Открытие файла в режиме только для запси

      textFile.write(enterTextNote.toPlainText().toUtf8());                       // Запись в файл содержимого поле TextEdit
      notemodel->appendData(textFile);                                            // Сообщить моделе, что добавился новый текствоый файл

      textFile.close();                                                           // После завершения работы, сохранить данные и закрыть файл
      trayicon->setVisible(true);
      trayicon->showMessage("Text Note", "The text note has been created.");      // Вывод информации о создании заметки
    } );
    connect(&saveButtun, &QPushButton::clicked, textNoteWindow, &QDialog::close);   // После сохранения данных - вернуться в меню заметок

    /* ====================================================== РАБОТА С ФУНКЦИОНАЛОМ ================================================= */

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ УПРАВЛЕНИЕ КОМПОНОВКОЙ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    textTitleFormLayout.addRow(tr("Title: "), &textNoteTitle);

    textNoteLayoutButtons.addStretch(1);
    textNoteLayoutButtons.addWidget(&saveButtun);
    textNoteLayoutButtons.addWidget(&cancelButton);

    textNoteVBoxLayout.addLayout(&textTitleFormLayout);
    textNoteVBoxLayout.addWidget(&enterTextNote);
    textNoteVBoxLayout.addLayout(&textNoteLayoutButtons);

    textNoteWindow->setLayout(&textNoteVBoxLayout);                              // Установка компоновщика в качестве основного

    textNoteWindow->exec();
}

void note::createVoiceNote()
{   // Слот для создания голосовой заметки
    /* -------------------------------------------- СОЗДАНИЕ ОБЪЕКТОВ ОКНА ТЕКСТОВЫХ ЗАМЕТОК ---------------------------------------- */
    QDialog *voiceNoteWin = new QDialog();

    voiceNoteWin->setWindowTitle(tr("Create new Voice note"));
    voiceNoteWin->setWindowIcon(QIcon(":/morningstar_resources/icons/microphone_icon.png"));

    QVBoxLayout voiceNoteVBoxLayout(voiceNoteWin);                              // Компоновщик для размещения в нем кнопок окна

    QPushButton recordingStartButton(tr("Start"));                              // Кнопка для начала записи звука
    QPushButton recordingStopButton(tr("Stop"));                                // Кнопка для завершения записи звука
    QPushButton returnButton(tr("Return"));                                     // Кнопка для возврата в меню заметок

    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ ПОДКЛЮЧЕНИЕ К СИГНАЛАМ ++++++++++++++++++++++++++++++++++++++++++++++++ */
    connect(&returnButton, &QPushButton::clicked, voiceNoteWin, &QDialog::close);
    connect(&recordingStartButton, &QPushButton::clicked, this, &note::recorderStart);
    connect(&recordingStopButton, &QPushButton::clicked, this, &note::recorderStop);

    /* ====================================================== РАБОТА С ФУНКЦИОНАЛОМ ================================================= */
    audioForm.setChannelCount(2);                          // Количество каналов (1 - моно, 2 - стерео и т.д)
    audioForm.setByteOrder(QAudioFormat::LittleEndian);    // Порядок байтов (LittleEndian - от младшего к старшему, BigEndian - от старшего к младшему)
    audioForm.setCodec("audio/pcm");                       // Установка режима шифратора/дешифратора (обычно ставится "audio/pcm")
    audioForm.setSampleSize(8);                            // Уровень выборки Импульсно-Кодовой Модуляции (pcm)
    audioForm.setSampleRate(44100);                         // Скорость оцифровки (количество отчетов в 1 сек)
    audioForm.setSampleType(QAudioFormat::UnSignedInt);    // Численное представлени выборки (для pcm обычно SignedInt или UnSignedInt)

    audioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();

    if(!audioDeviceInfo.isFormatSupported(audioForm))
    {
        qWarning() << "Default format not supported, trying to use the nearest.";
        trayicon->setVisible(true);
        trayicon->showMessage("Warning!", "Default format not supported, trying to use the nearest.", QIcon(":/image/icon/info_icon.png"), 3000);
        audioForm = audioDeviceInfo.nearestFormat(audioForm);
    }
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ УПРАВЛЕНИЕ КОМПОНОВКОЙ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    voiceNoteVBoxLayout.addWidget(&recordingStartButton);
    voiceNoteVBoxLayout.addWidget(&recordingStopButton);
    voiceNoteVBoxLayout.addStretch(1);
    voiceNoteVBoxLayout.addWidget(&returnButton);

    voiceNoteWin->setLayout(&voiceNoteVBoxLayout);                              // Установка компоновщика в качестве основного

    voiceNoteWin->exec();
}

void note::showNote(const QModelIndex & index)
{   // Слот для просмотра заметки

    QString noteType = notemodel->noteType(index);

    if("txt" == noteType)
    {       /* Если тип заметки - текстовая, то создается соотвествующее окно */
        QDialog *showTextNoteWin = new QDialog();
        showTextNoteWin->setWindowTitle(tr("Show text note"));
        showTextNoteWin->setWindowIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"));

        QSystemTrayIcon *trayiconShowTextNote = new QSystemTrayIcon(QIcon(":/morningstar_resources/icons/clipboard_icon.png"), showTextNoteWin);

        QVBoxLayout *textNoteVLayout = new QVBoxLayout(showTextNoteWin);

        QTextEdit showTextNote;
        showTextNote.setReadOnly(true);

        // Получение полного имени файла (путь + имя файла с суффиксом), в зависимости от выбранного элемента в списке заметок
        QString textNoteFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)
                                    + "/MorningStar" + "/MorningStar_Reliza" + "/TextNote" + "/"
                                    + notemodel->noteName(index) + '.' + noteType;

        QFile textNoteFile(textNoteFilePath);
        textNoteFile.open(QIODevice::ReadOnly);
        if(textNoteFile.isOpen())
            showTextNote.setText(textNoteFile.readAll());
        else
        {
            trayiconShowTextNote->setVisible(true);
            trayiconShowTextNote->showMessage(tr("Text note"),tr("File read error"));
        }
        trayiconShowTextNote->setVisible(false);


        textNoteVLayout->addWidget(&showTextNote);

        setLayout(textNoteVLayout);

        textNoteFile.close();
        showTextNoteWin->exec();
    }
    if("wav" == noteType)
    {       /* Если тип заметки - голосовая, то создается соотвествующее окно */
        QDialog *playVoiceNoteWin = new QDialog();
        playVoiceNoteWin->setWindowTitle(tr("Play voice note"));
        playVoiceNoteWin->setWindowIcon(QIcon(":/morningstar_resources/icons/microphone_icon.png"));

        // Получение полного имени файла (путь + имя файла с суффиксом), в зависимости от выбранного элемента в списке заметок
        QString voiceNoteFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)
                                    + "/MorningStar" + "/MorningStar_Reliza" + "/VoiceNote" + "/"
                                    + notemodel->noteName(index) + '.' + noteType;
        /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ++++++++++++++++++++++++++++++++++++++++++++++++ */
        QVBoxLayout *voiceNoteVLayout = new QVBoxLayout(playVoiceNoteWin);
        QHBoxLayout layoutSlider;
        QSlider audioProgressLine;
        QPushButton playAndStopButton;
        QPushButton stopButton;
        QMediaPlayer *mediaPlayer = new QMediaPlayer;
        QLabel currentAudioTime;                                        // Текстовая метка для хранения текущего времени проигрывания аудио-файла
        QLabel durationAudioTime;                                       // Текстовая метка для хранения максимального времени аудио-файла
        QTimer currentAudioTimer;

        /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ НАСТРОЙКА ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        audioProgressLine.setOrientation(Qt::Horizontal);
        audioProgressLine.setMinimum(0);

        stopButton.setText(tr("Stop"));

        mediaPlayer->setMedia(QUrl::fromLocalFile(voiceNoteFilePath));
        mediaPlayer->setVolume(50);
        mediaPlayer->play();

        currentAudioTime.setText(tr("Current"));
        durationAudioTime.setText(tr("End"));

        int curSec = 00;
        int curMin = 00;
        int curHour = 00;

        int sliderPosition = 0;     // Для продвижения слайдера, в зависимости от пройденного времени (сек)

        /* ====================================================== ПОДКЛЮЧЕНИЕ К СИГНАЛАМ ================================================ */
        connect(mediaPlayer, &QMediaPlayer::durationChanged, playVoiceNoteWin,
                [&]()
        {
            int dMSec = mediaPlayer->duration() % 1000;                  // Получение части мсек
            int dMin = (mediaPlayer->duration() / 1000) / 60;            // Получение части мин
            int dSec = (mediaPlayer->duration() / 1000) - (dMin * 60);   // Получени части сек
            int dHour = 0;
            if(dMin > 60)
            {
                dHour =  dMin / 60;
                dMin-=(dHour*60);                                        // Изменение количества минут, так как значение превысило 60
                durationAudioTime.setText(QString(QString::number(dHour) + ":" +QString::number(dMin) + ":" + QString::number(dSec) + "." + QString::number(dMSec)));
            }
            else
                durationAudioTime.setText(QString(QString::number(dMin) + ":" + QString::number(dSec) + "." + QString::number(dMSec)));

            audioProgressLine.setMaximum(mediaPlayer->duration() / 1000);     // Аккуратно! Если значение будет слишком большое (больше Инта), то будет плохо

        }
        );

        currentAudioTimer.start(1000);
        connect(&currentAudioTimer, &QTimer::timeout, playVoiceNoteWin, [&]()
        {
            if(mediaPlayer->state() == QMediaPlayer::PlayingState)
            {
                 curSec+=1;
                 if(curSec>60)
                 {
                      curSec = 00;
                      curMin+=1;
                 }
                if(curMin>60)
                {
                    curMin = 00;
                    curHour+=1;
                }

                if(curHour <= 0)
                    currentAudioTime.setText(QString(QString::number(curMin) + ":" + QString::number(curSec)));
                else
                    currentAudioTime.setText(QString(QString::number(curHour) + ":" + QString::number(curMin) + ":" + QString::number(curSec)));

                sliderPosition+=1;
                audioProgressLine.setSliderPosition(sliderPosition);
            }
            if(mediaPlayer->state() == QMediaPlayer::StoppedState)
            {
                currentAudioTime.setText("00:00");
                sliderPosition = 0;
                audioProgressLine.setSliderPosition(sliderPosition);
            }
        }
                );

        connect(&stopButton, &QPushButton::clicked, playVoiceNoteWin, [&](){mediaPlayer->stop(); });
        connect(&stopButton, &QPushButton::clicked, playVoiceNoteWin, &QDialog::accept);
        connect(playVoiceNoteWin, &QDialog::finished, playVoiceNoteWin, [&](){mediaPlayer->stop(); });

        /* ...................................................... УПРАВЛЕНИЕ КОМПОНОВКОЙ ................................................ */

        layoutSlider.addWidget(&currentAudioTime);
        layoutSlider.addWidget(&audioProgressLine);
        layoutSlider.addWidget(&durationAudioTime);

        voiceNoteVLayout->addLayout(&layoutSlider);
        voiceNoteVLayout->addWidget(&playAndStopButton);
        voiceNoteVLayout->addWidget(&stopButton);

        setLayout(voiceNoteVLayout);

        playVoiceNoteWin->exec();
    }


}

void note::deleteNote()
{   // Слот для удаления заметки

    // Потом реализую удаление нескольких заметок
    //QItemSelectionModel itemselectionmodel(notemodel);
    //QModelIndexList miList = tableview->selectionModel()->selectedRows();

    QModelIndex curIndex = tableview->selectionModel()->currentIndex();
    notemodel->removeData(curIndex.row());


}

void note::noteRead()
{   // Слот для проверки на существование директории и заметок в ней
    trayicon->setVisible(true);
    trayicon->showMessage(tr("Note"), tr("Checking files ..."));

    QString loc = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);  // "~/.config/<APPNAME>", "C:/Users/<USER>/AppData/Local/<APPNAME>"

    QDir morningstar_headDir(loc + "/MorningStar");
    QDir morningstar_currentVersionDir(loc + "/MorningStar" + "/MorningStar_Reliza");
    QDir morningstar_textnoteDir(loc + "/MorningStar" + "/MorningStar_Reliza" + "/TextNote");
    QDir morningstar_voicenoteDir(loc + "/MorningStar" + "/MorningStar_Reliza" + "/VoiceNote");

    if(!morningstar_headDir.exists())                    // Проверка на наличие главной директории приложения
    {
        trayicon->setVisible(true);
        trayicon->showMessage(tr("Note"),tr("The main application directory was not found.") + '\n' + tr(" A new one will be created."));
        morningstar_headDir.setPath(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation));
        morningstar_headDir.mkdir("MorningStar");
    }
    if(!morningstar_currentVersionDir.exists())         // Проверка на наличие директори текущей версии приложения
    {
        trayicon->setVisible(true);
        trayicon->showMessage(tr("Note"), tr("The directory for the current version of the application was not found.") + '\n' + tr(" A new one will be created."));
        morningstar_currentVersionDir.setPath(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar");
        morningstar_currentVersionDir.mkdir("MorningStar_Reliza");
    }
    if(!morningstar_textnoteDir.exists())
    {
        trayicon->setVisible(true);
        trayicon->showMessage(tr("Note"), tr("The directory for text notes does not exist!") + '\n' + tr(" A new one will be created."));
        morningstar_textnoteDir.setPath(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza");
        morningstar_textnoteDir.mkdir("TextNote");

    }
    if(!morningstar_voicenoteDir.exists())
    {
        trayicon->setVisible(true);
        trayicon->showMessage(tr("Note"), tr("The directory for voice memos does not exist!") + '\n' + tr(" A new one will be created."));
        morningstar_voicenoteDir.setPath(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza");
        morningstar_voicenoteDir.mkdir("VoiceNote");
    }

    // Первоначальное считывание файлов из директорий с заметками
    QString locNote = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza";
    // Считывание текстовых заметок
    QDir textnoteDir(locNote + "/TextNote");
    if(0 != textnoteDir.count())
    {   // Если в директории есть файлы, то происходит выполнение инструкций

        // Итерация в директории по файлам:         std::filesystem::directory_iterator(dirName);

        // QFileInfo::suffix()         - возвращает суффикс(расширение) файла , н-р "txt"        (QString)
        // QFileInfo::baseName()       - возвращает базовое имя файла без пути                   (QString)
        // QFileInfo::BirthTime()      - возвращает дату и время создания / рождения файла       (QDateTime)

        // QFileInfo::lastModified()   - возвращает дату и время последнего изменения файла      (QDateTime) *пригодится для другого
        QDirIterator textnoteDirIter(textnoteDir);
       // int i = 0;
      //  while(textnoteDirIter.hasNext())                                // Пока есть заметки
       // {
            //notemodel.setData(QModelIndex(),textnoteDirIter.next());
        //    i++;
       // }

    }

    // Считывание голосовых заметок
    QDir voicenoteDir(locNote + "/VoiceNote");
    if(0 != voicenoteDir.count())
    {   // Если в директории есть файлы, то происходит выполнение инструкций

    }

}

void note::recorderStart()
{   // Слот для запуска записи
    generateNameForVoiceNote();                                                   // Вызов метода для генерации имени для файла перед созданием нового файла
    audioFile.setFileName(*nameVoiceNote);
    audioFile.open( QIODevice::WriteOnly | QIODevice::Truncate );
    audioInput = new QAudioInput(audioForm, this);
    connect(audioInput, &QAudioInput::stateChanged, this, &note::handleStateChanged);
    audioInput->start(&audioFile);

}

void note::recorderStop()
{   // Слот для окончания записи
    audioInput->stop();                     // Остановка записи
    writeHeader();                          // Запись в файл заголовков
    notemodel->appendData(audioFile);       // Сообщить моделе, что произошло добавление нового аудио-файла
    audioFile.close();                      // Закрытие файла

    disconnect(audioInput, &QAudioInput::stateChanged, this, &note::handleStateChanged);

    trayicon->setVisible(true);
    trayicon->showMessage("Voice Note Info", "Sound recording is complete.");

}

void note::handleStateChanged()
{  // Слот по информированию о состоянии потока записи
    switch (audioInput->state())
    {
        case QAudio::StoppedState:
            if(audioInput->error() != QAudio::NoError)
            {
                trayicon->setVisible(true);
                trayicon->showMessage("Voice Note Info", "Error, sound recording is not possible!");
            }
            else
            {
                audioInput->stop();
            }
            break;

       case QAudio::ActiveState:
       {
            trayicon->setVisible(true);
            trayicon->showMessage("Voice Note Info", "Sound recording in progress.");
            break;
       }

    }

}

void note::writeHeader()
{   // Запись заголовка в аудио-файл
    QFileInfo sizefile;
    sizefile.setFile(audioFile);
    quint32 datasize = sizefile.size();         // Размер аудио-данных, которые были записаны в файл (без учета заголовков)

    audioFile.seek(0);                          // Установка "каретки" в самое начало файла

    RIFFHeader  riffheader;                     // Создание объекта RIFF заголовка
    WAVEHeader  waveheader;                     // Создание объекта WAVE заголовка
    DATAHeader  dataheader;                     // Создание объекта DATA заголовка

    for(int i = 0; i < 4; ++i)                  // Запись симоволов RIFF
        riffheader.chunkId[i] = "RIFF"[i];
    riffheader.chunkSize = sizeof(quint32) + sizeof(WAVEHeader) + sizeof(quint64) + dataheader.subchunk2Size;      // Отсавшийся размер RIFF цепочки

    for(int i = 0; i < 4; ++i)                  // Запись симоволов WAVE
        riffheader.format[i] = "WAVE"[i];

    for(int i = 0; i < 4; ++i)                  // Запись симоволов fmt
        waveheader.subchunk1Id[i] = "fmt "[i];
    waveheader.subchunk1Size = (sizeof(WAVEHeader) - sizeof(quint64));      // Оставшийся размер WAVEHeader, без subchunk1Id и subchunk1Size
    waveheader.audioFormat = 1;                 // Установка аудио формата (для PCM = 1 , линейное квантование)
    waveheader.numChannels = 2;                 // Установка количества каналов (1 = Моно, 2 = Стерео и т.д)
    waveheader.sampleRate = 44100;               // Установка частоты дискретизации (Гц)
    waveheader.bitsPerSample = 8;               // Установка количества бит в sample (глубина звучания, например 8 бит, 16 бит и т.д)
    waveheader.byteRate =   waveheader.sampleRate
                        *   waveheader.numChannels
                        *   waveheader.bitsPerSample / 8;         // Установка количества байт, переданных за секунду воспроизведения
    waveheader.blockAlign = waveheader.numChannels
                          * waveheader.bitsPerSample / 8;       // Установка количества байт для одного sample

    for(int i = 0; i < 4; ++i)                  // Запись симоволов data
        dataheader.subchank2Id[i] = "data"[i];
    dataheader.subchunk2Size = datasize;        // Установка размера данных аудио-файла без учета RIFF-цепочки

    // Запись заголовков в начало файла
    {
        audioFile.write(reinterpret_cast<char*>(&riffheader.chunkId),sizeof(char[4]));
        audioFile.write(reinterpret_cast<char*>(&riffheader.chunkSize),sizeof(quint32));
        audioFile.write(reinterpret_cast<char*>(&riffheader.format),sizeof(char[4]));
        audioFile.write(reinterpret_cast<char*>(&waveheader.subchunk1Id),sizeof(char[4]));
        audioFile.write(reinterpret_cast<char*>(&waveheader.subchunk1Size),sizeof(quint32));
        audioFile.write(reinterpret_cast<char*>(&waveheader.audioFormat),sizeof(quint16));
        audioFile.write(reinterpret_cast<char*>(&waveheader.numChannels),sizeof(quint16));
        audioFile.write(reinterpret_cast<char*>(&waveheader.sampleRate),sizeof(quint32));
        audioFile.write(reinterpret_cast<char*>(&waveheader.byteRate),sizeof(quint32));
        audioFile.write(reinterpret_cast<char*>(&waveheader.blockAlign),sizeof(quint16));
        audioFile.write(reinterpret_cast<char*>(&waveheader.bitsPerSample),sizeof(quint16));
        audioFile.write(reinterpret_cast<char*>(&dataheader.subchank2Id),sizeof(char[4]));
        audioFile.write(reinterpret_cast<char*>(&dataheader.subchunk2Size),sizeof(quint32));
    }
}

void note::generateNameForTextNote()
{ // Слот для генерации имени для текстовой заметки (в зависимости от текущего времени и даты), если не было введено название
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QString textNoteLoc = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza" + "/TextNote";

    // Установка название файла исходя из вида заметки (текстовая) и момента создания (текущая дата + текущее время)
    *nameTextNote = textNoteLoc + "/morningstar-textnote_" + QString::number(date.year())     + "-"
                                                           + QString::number(date.month())    + "-"
                                                           + QString::number(date.day())      + "_"
                                                           + QString::number(time.hour())     + "-"
                                                           + QString::number(time.minute())   + "-"
                                                           + QString::number(time.second())   + ".txt";
}

void note::generateNameForVoiceNote()
{ // Слот для генерации имени для голосовой заметки (в зависимости от текущего времени и даты)
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QString voiceNoteLoc = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza" + "/VoiceNote";

    // Установка название файла исходя из вида заметки (голосовая) и момента записи (текущая дата + текущее время)
    *nameVoiceNote = voiceNoteLoc + "/morningstar-voicenote_" + QString::number(date.year())     + "-"
                                                              + QString::number(date.month())    + "-"
                                                              + QString::number(date.day())      + "_"
                                                              + QString::number(time.hour())     + "-"
                                                              + QString::number(time.minute())   + "-"
                                                              + QString::number(time.second())   + ".wav";
}

note::~note() {}
