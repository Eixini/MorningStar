#include "note.h"

note::note(QDialog *parent) : QDialog(parent)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~  ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное меню
    addButton = new QPushButton("Добавить заметку", this); // Создание кнопки для добавления новой заметки
    editButton = new QPushButton("Редактировать заметку", this); // Создание кнопки для редактирования существующей заметки
    removeButton = new QPushButton("Удалить заметку" ,this); // Создание кнопки для удаления заметки

    hbox = new QHBoxLayout(this); // Создание горизонтального компоновщика
    vbox = new QVBoxLayout(); // Создание вертикального компоновщика

    notelist = new QListWidget(this); // Создание списка

    QFile noteFile("/home/eixini/Рабочий стол/note_morningstar.txt"); // Создание указателя для работы с файлом, где содержатся заметки

    // +++++++++++++++++++++++++   НАСТРОЙКА ФУНКЦИОНАЛА   ++++++++++++++++++++++++++++++


    // ++++++++++++++++++++++++++++++ РАБОТА С ФАЙЛОМ +++++++++++++++++++++++++++++++++++



    // ***********************  ПОДКЛЮЧЕНИЕ СИГНАЛОВ К СЛОТАМ  **************************

    connect(mainmenu, &QPushButton::clicked, this, &QDialog::accept); // При нажатии на кнопку, будет произведен возврат в главное меню
    connect(addButton, &QPushButton::clicked, this, &note::addNote); // При нажатии на кнопку, появляется окно для создания новой заметки
    connect(editButton, &QPushButton::clicked,this, &note::editNote); // При нажатии на кнопку, появляется окно для редактирования заметки
    connect(removeButton, &QPushButton::clicked, this, &note::removeNote); // При нажатии на кнопку, выбранная заметка удаляется

    // ^^^^^^^^^^^^^^^^^^^^^^^     УПРАВЛЕНИЕ КОМПОНОВКОЙ     ^^^^^^^^^^^^^^^^^^^^^^^^^^^

    // Настройка компоновки кнопок
    vbox->addSpacing(5); // Установка расстояния между кнопками
    vbox->addStretch(1); // Добавление коэффициента растяжения сверху
    vbox->addWidget(addButton);
    vbox->addWidget(editButton);
    vbox->addWidget(removeButton);
    vbox->addStretch(1); // Добавление коэффициента растяжения снизу
    vbox->addWidget(mainmenu);


    hbox->addWidget(notelist);
    hbox->addLayout(vbox);

    setLayout(hbox); // Установка виджета в качестве основного

}


void note::addNote()
{
// Добавление новой заметки

    notelist->addItem("New Note"); // Установка названия заметки (элемента QListWidget)


}

void note::showNote()
{
// Просмотр заметки
// Режим для названия и содержания заметки - только чтение


}

void note::editNote()
{
// Редактирвоание существующей заметки

    editNoteWin = new QDialog(this);
    editNoteWin->show();

    editTitleNote = new QLineEdit(this); // Создание текстовой строки для названия заметки
    editNoteVBox = new QVBoxLayout(editNoteWin); // Создание компоновщика
    formLineEdit = new QFormLayout(); // СОздание компоновщика для подписи текста
    hboxForEditButtons = new QHBoxLayout(); // Создание горизонтального компоновщика для кнопок
    editAccept = new QPushButton("Сохранить",this); // Создание кнопки для принятия изменений
    editCancel = new QPushButton("Отменить", this); // Создание кнопки для отмены изменений

    noteName = new QString("New Note"); // Создание переменной для хранения введеного текста


    // +++++++++++++++++++ Работа с Сигналами ++++++++++++++++++++++++++++

    connect(editAccept,&QPushButton::clicked,this,&QDialog::accept);
    connect(editCancel,&QPushButton::clicked,this,&QDialog::close);
    connect(editTitleNote, &QLineEdit::editingFinished,this,&note::setNoteNameText);

    // ======================== Компноновка ==============================

    formLineEdit->addRow("Название: ",editTitleNote);
    editNoteVBox->addLayout(formLineEdit);

    hboxForEditButtons->addWidget(editAccept);
    hboxForEditButtons->addWidget(editCancel);

    editNoteVBox->addLayout(hboxForEditButtons);

// ::::::::::::::::::::::::  ФУНКЦИОНАЛ ОКНА   :::::::::::::::::::::::::::::::::::::

    notelist->selectedItems()[0]->setText(*noteName); // Установка текста в элемент QListWidget

// ------------------ Работа с Файлом --------------------------------





}

void note::removeNote()
{
// Удаление заметки
    if(notelist)
    {
               QList< QListWidgetItem* > items = notelist->selectedItems();
               foreach( QListWidgetItem* item, items )
               {
                   int row = notelist->row( item );
                   notelist->takeItem( row );
                   delete item;
               }
    }

}

void note::setNoteNameText()
{
    notelist->selectedItems()[0]->setText(editTitleNote->text()); // Установка текста в элемент QListWidget
    *noteName = editTitleNote->text();
}

void note::note_read() // Слот для считывания заметок из файла и запись их в объект класса QListWidget
{
    QMessageBox::warning(this, "Инфо","Идет считывание данных из файла заметок"); // Пока что нужно для отладки

    // Проверка, существует ли файл

    // Проверка , открыт ли файл, доступен ли он для считывание информации и т.д

    QFile noteTxt("/home/eixini/note_morningstar.txt"); // Создание объекта для работы с файлом
    noteTxt.open(QIODevice::ReadOnly); // Открытие файла (и установка режима - только чтение)

    if(noteTxt.isOpen()) // Проверка, открыт ли файл
    {    QMessageBox::warning(this, "Инфо","Файл успешно открыт!"); }
    else
    {   QMessageBox::warning(this, "Ошибка","Файл не открыт!"); }

    // -------------------------- СЧИТЫВАНИЕ ДАННЫХ ИЗ ТЕКСТОВОГО ФАЙЛА И ЗАПИСЬ В СПИСОК ---------------------------- //
    QString noteContent; // объект строкового типа для временного хранения содержимого определенной строки
    noteContent = noteTxt.readLine(); // Считывание информации
    notelist->addItem(noteContent); // Создание объекта QListWidget и устанвока имени из файла

    noteTxt.close(); // Закрытие файла
}

note::~note() {}
