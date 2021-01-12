#include "settings.h"

settings::settings(QDialog *parent) : QDialog(parent)
{
// ------------------------- ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ------------------------------

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное окно
    folderLine = new QLineEdit(this);// Создание строчки для ввода пути для заметок
    exampleFolder = new QLabel("Пример: /home/eixini/Desktop/Eixini/Notes/ ",this); // Создание текстовой метки для показа примера

    vbox = new QVBoxLayout(this); // Создание вертикального компоновщика
    formbox = new QFormLayout(); // Создание компоновщика для текстовых меток

// ------------------------- НАСТРОЙКА КОМПОНЕНТОВ -------------------------------


    mainmenu->setFixedSize(180,30); // Установка фиксированного размера кнопки

// ---------------------- ПОДКЛЮЧЕНИЕ СИГНАЛОВ-СЛОТОВ ----------------------------

    connect(mainmenu,&QPushButton::clicked, this, &QDialog::accept); // сигнал Нажатие кнопки - принятие и возврат к главному окну

// -------------------------- НАСТРОЙКИ КОМПОНОВКИ -------------------------------

    formbox->addRow("Путь для файлов заметок: ",folderLine);

    vbox->addLayout(formbox);
    vbox->addWidget(exampleFolder,1,Qt::AlignTop);

    vbox->addWidget(mainmenu, 1, Qt::AlignHCenter);


    setLayout(vbox); // Установка главного компоновщика
}



settings::~settings() {}
