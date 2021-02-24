#include "settings.h"

settings::settings(QDialog *parent) : QDialog(parent)
{
// ------------------------- ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ------------------------------

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное окно
    okButton = new QPushButton("Применить",this); // Кнопка для применения файлового пути
    folderLine = new QLineEdit(this);// Создание строчки для ввода пути для заметок
    exampleFolder = new QLabel("Пример: /home/eixini/Desktop/Eixini/Notes/ ",this); // Создание текстовой метки для показа примера

    vbox = new QVBoxLayout(this); // Создание вертикального компоновщика
    formbox = new QFormLayout(); // Создание компоновщика для текстовых меток
    sbox = new QHBoxLayout(); // Создание компоновщика для текущего файлового пути
    buttonBox = new QHBoxLayout(); // Создание компоновщика для размещения кнопок

    selectLabel = new QLabel("Текущий файловый путь: "); // Создание текстовой метки для строки с указанием файлового пути
    selectPath = new QLineEdit(this); // Создание строки для файлового пути

    QString *pathText; // Для временного хранения текста

// ------------------------- НАСТРОЙКА КОМПОНЕНТОВ -------------------------------


    mainmenu->setFixedSize(180,30); // Установка фиксированного размера кнопки
    okButton->setFixedSize(180,30);
    selectPath->setReadOnly(true); // Строка не доступна для пользовательского ввода

// ---------------------- ПОДКЛЮЧЕНИЕ СИГНАЛОВ-СЛОТОВ ----------------------------

    connect(mainmenu,&QPushButton::clicked, this, &QDialog::accept); // сигнал Нажатие кнопки - принятие и возврат к главному окну
    connect(okButton, &QPushButton::clicked,this, &settings::copyPath); // сигнал Нажатие кнопки - применение введеного пути для хранения файлов

// -------------------------- НАСТРОЙКИ КОМПОНОВКИ -------------------------------

    formbox->addRow("Путь для файлов заметок: ",folderLine);

    sbox->addWidget(selectLabel);
    sbox->addWidget(selectPath);

    vbox->addLayout(formbox);
    vbox->addWidget(exampleFolder,1,Qt::AlignTop);
    vbox->addLayout(sbox);

    buttonBox->addWidget(okButton);
    buttonBox->addWidget(mainmenu);

    vbox->addLayout(buttonBox);

    setLayout(vbox); // Установка главного компоновщика
}

void settings::copyPath()
{
// Нужно сделать проверку, ввел ли пользоватль что-нибудь в строку для указания пути или нет. Если нет - показать сообщение, что строка пуста

    // Если пользователь ввел что-нибудь (пофиг, не обязательно путь) , то содержимое копируется и вставляется в другую строку.


}

settings::~settings() {}
