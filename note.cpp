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



    // +++++++++++++++++++++++++   НАСТРОЙКА ФУНКЦИОНАЛА   ++++++++++++++++++++++++++++++

    noteName = new QString("New Note"); // Создание переменной для хранения введеного текста


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


    editNoteWin = new QDialog(this); // Создание диалогового окна

    editTitleNote = new QLineEdit(editNoteWin); // Создание текстовой строки для названия заметки
    editTextNote = new QTextEdit(this); // Создание текстового объекта для содержания заметки
    editNoteVBox = new QVBoxLayout(editNoteWin); // Создание компоновщика
    formLineEdit = new QFormLayout(); // СОздание компоновщика для подписи текста
    hboxForEditButtons = new QHBoxLayout(); // Создание горизонтального компоновщика для кнопок
    editAccept = new QPushButton("Сохранить",this); // Создание кнопки для принятия изменений
    editApply = new QPushButton("Применить",this); // Создание кнопки для применения изменений
    editCancel = new QPushButton("Отменить", this); // Создание кнопки для отмены изменений
    LabelEditTextNote = new QLabel("Содержание: ",this); // СОздание текстовой метки для текста заметки

    editNoteWin->setWindowTitle("Редактирование заметки");
    editNoteWin->setWindowIcon(QIcon("/home/eixini/Рабочий стол/Eixini/Qt/Projects/MorningStar/File_for_Project/icons/keyboard_icon"));

    // Подредактировать сигналы
    connect(editAccept,&QPushButton::clicked,editNoteWin,&QDialog::accept);
    connect(editCancel,&QPushButton::clicked,editNoteWin,&QDialog::close);
    connect(editTitleNote, &QLineEdit::editingFinished,this,&note::setNoteNameText);

    // Компноновка

    formLineEdit->addRow("Название: ",editTitleNote);
    editNoteVBox->addLayout(formLineEdit);
    editNoteVBox->addWidget(LabelEditTextNote);
    editNoteVBox->addWidget(editTextNote);

    hboxForEditButtons->addWidget(editAccept);
    hboxForEditButtons->addWidget(editApply);
    hboxForEditButtons->addWidget(editCancel);

    editNoteVBox->addLayout(hboxForEditButtons);

// ::::::::::::::::::::::::  ФУНКЦИОНАЛ ОКНА   :::::::::::::::::::::::::::::::::::::

    notelist->selectedItems()[0]->setText(*noteName);


    editNoteWin->exec();
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

// Слот для применения изменений
void note::setNoteNameText()
{
    *noteName = editTitleNote->text();
}



note::~note() {}
