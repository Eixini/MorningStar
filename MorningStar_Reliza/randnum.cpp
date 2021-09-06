#include "randnum.h"
#include "QNixieNumber/qnixienumber.h"
#include <random>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QTimer>

#include <QThread>
#include <QCoreApplication>
#include <QMessageBox>

/*          Вопросы, требующие внимания:

    - сгенерированное число отобращать поэтапно с перебором предшествующих чисел n-сегмента
       (т.е если выпало 527 - то чтобы отобразить 5, нужно сначала отобразить 0,1,2,3,4 и только потом 5...
       или же сделать иммитацию разных чисел);

*/

int randnum::randnumResult = 0;                         // Инициализация статической переменной для хранения результатов генерации случайного числа

randnum::randnum(QDialog *parent) : QDialog(parent)
{
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ++++++++++++++++++++++++++++++++++++++++++++++++ */
    {
        trayicon = new QSystemTrayIcon(QIcon(":/morningstar_resources/icons/ball_icon.png"),this);
        timer = new QTimer(this);


        for(auto i = 0; i < SIZE_ARRAY; ++i)
        {
            NixieDisplay[i] = new QNixieNumber(this, QNixieNumber::REALNIXIE);
            NixieDisplay[i]->setSegmentsCount(1);
            NixieDisplay[i]->display(0);
        }
    }
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ НАСТРОЙКА ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        generateRandNumButton.setText(tr("Generate"));
        toMainMenuButton.setText(tr("To main menu"));

        label_min.setText(tr("Minimal: "));
        label_max.setText(tr("Maximal: "));

        spinbox_min.setRange(0, std::numeric_limits<int>::max() - 1);
        spinbox_max.setRange(1, std::numeric_limits<int>::max());

        splitRandnumResult.reserve(10);
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

    for(auto i = 0; i < SIZE_ARRAY; ++i)
            nixieDisplayLayout.addWidget(NixieDisplay[i]);
    headVerticalLayout.addLayout(&nixieDisplayLayout);

    headVerticalLayout.addLayout(&spinboxHorizontalLayout);
    headVerticalLayout.addWidget(&generateRandNumButton);
    headVerticalLayout.addWidget(&toMainMenuButton);

    setLayout(&headVerticalLayout);
}

void randnum::generate()
{

    std::mt19937_64 engine {std::random_device{}()};
    if(spinbox_min.value() < spinbox_max.value())
    {
        std::uniform_int_distribution<> distributin {spinbox_min.value(), spinbox_max.value()};
        randnumResult = distributin(engine);

        interResult = randnumResult;

        for(auto i = 0; i < SIZE_ARRAY; i++)
                splitRandnumResult.push_back(split(interResult));

        std::reverse(splitRandnumResult.begin(), splitRandnumResult.end());

        for(auto i = 0; i < SIZE_ARRAY; ++i)            // Очистка дисплея перед показом нового числа
            NixieDisplay[i]->display(0);

        for(auto i = SIZE_ARRAY - 1; i >= 0; --i)
        {
                for (auto j = 0 ; j <= splitRandnumResult[i]; j++)
                {
                    NixieDisplay[i]->display(j);
                    QCoreApplication::processEvents();          // Для того, чтобы во время цикла менялись цифры
                    QThread::msleep(250);
                }
        }

    }
    else
    {
        trayicon->setVisible(true);
        trayicon->showMessage("Randnum", tr(R"delimiter(Range error. "Min" must be strictly less than "Max")delimiter"));
    }

}

int randnum::split(int number)
{
    // Splitting a number
    int n = number % 10;
    interResult = (number - n) / 10;
    return n;
}

randnum::~randnum() {}
