#include "randnum.h"
#include "QNixieNumber/qnixienumber.h"
#include <random>

#include <QMessageBox>

/*          Вопросы, требующие внимания:

    - реализовать генерацию случайный чисел на основе <random> C++11;
    - выбрать максимальный диапазон генерации случайных чисел (т.е тип данные, но нужен unsigned (int,long);
    - в зависимости от разрядности максимального допустимого числа, установить количество сегментов QNixieNumber;
    - сгенерированное число отобращать поэтапно с перебором предшествующих чисел n-сегмента
       (т.е если выпало 527 - то чтобы отобразить 5, нужно сначала отобразить 0,1,2,3,4 и только потом 5...
       или же сделать иммитацию разных чисел);

*/

int randnum::randnumResult = 0;                         // Инициализация статической переменной для хранения результатов генерации случайного числа

randnum::randnum(QDialog *parent) : QDialog(parent)
{
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ++++++++++++++++++++++++++++++++++++++++++++++++ */
    {
        showRandnumResult = new QNixieNumber(this, QNixieNumber::REALNIXIE);
    }
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ НАСТРОЙКА ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        generateRandNumButton.setText(tr("Generate"));
        toMainMenuButton.setText(tr("To main menu"));

        label_min.setText(tr("Minimal: "));
        label_max.setText(tr("Maximal: "));

        showRandnumResult->display(0);

        spinbox_min.setRange(0, std::numeric_limits<int>::max() - 1);
        spinbox_max.setRange(1, std::numeric_limits<int>::max());

        showRandnumResult->setSegmentsCount(10);

    }
    /* ====================================================== ПОДКЛЮЧЕНИЕ К СИГНАЛАМ ================================================ */
    {
        connect(&generateRandNumButton, &QPushButton::clicked, this, &randnum::generate);
        connect(&toMainMenuButton, &QPushButton::clicked, this, &QDialog::accept);
    }
    /* ...................................................... УПРАВЛЕНИЕ КОМПОНОВКОЙ ................................................ */

    spinboxHorizontalLayoutMin.addWidget(&label_min);
    spinboxHorizontalLayoutMin.addWidget(&spinbox_min);
    spinboxHorizontalLayoutMin.setStretch(1,1);
    spinboxHorizontalLayoutMax.addWidget(&label_max);
    spinboxHorizontalLayoutMax.addWidget(&spinbox_max);
    spinboxHorizontalLayoutMax.setStretch(1,1);
    spinboxHorizontalLayout.addLayout(&spinboxHorizontalLayoutMin);
    spinboxHorizontalLayout.addLayout(&spinboxHorizontalLayoutMax);

    headVerticalLayout.addWidget(showRandnumResult);
    headVerticalLayout.addLayout(&spinboxHorizontalLayout);
    headVerticalLayout.addWidget(&generateRandNumButton);
    headVerticalLayout.addWidget(&toMainMenuButton);

    setLayout(&headVerticalLayout);
}

void randnum::generate()
{
    QMessageBox::warning(this, tr("Information"), tr("The functionality is still under development."));


}

randnum::~randnum() {}
