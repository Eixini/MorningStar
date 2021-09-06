#ifndef QNIXIENUMBER_H
#define QNIXIENUMBER_H

#include <QWidget>

#include <QTimer>
#include <vector>
#include <array>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

class QNixieNumber : public QWidget
{
    Q_OBJECT

public:

    enum mode_ {NIXIE,REALNIXIE}; // Constant values for choosing a style

    QNixieNumber(QWidget *parent = nullptr, mode_ = NIXIE);
    ~QNixieNumber();

public slots:

int intValue() const;                     // Returns the current integer value
void display(int number = 0);             // Display nixie numbers
void setSegmentsCount(int value = 0);     // Sets the number of segments
void setStyle(mode_ mode);                // Setting the style of displayed digits

private:

    mode_ selectMode_;              // To store the selected style


    // For easy access to values
    std::array<QPixmap,10> NixieNumber
    {
            QPixmap(":/numbers/nixie_numbers/n0.png"),
            QPixmap(":/numbers/nixie_numbers/n1.png"),
            QPixmap(":/numbers/nixie_numbers/n2.png"),
            QPixmap(":/numbers/nixie_numbers/n3.png"),
            QPixmap(":/numbers/nixie_numbers/n4.png"),
            QPixmap(":/numbers/nixie_numbers/n5.png"),
            QPixmap(":/numbers/nixie_numbers/n6.png"),
            QPixmap(":/numbers/nixie_numbers/n7.png"),
            QPixmap(":/numbers/nixie_numbers/n8.png"),
            QPixmap(":/numbers/nixie_numbers/n9.png")
    };

    std::array<QPixmap,10> RealNixieNumber
    {
            QPixmap(":/numbers/realnixie_numbers/rn0.png"),
            QPixmap(":/numbers/realnixie_numbers/rn1.png"),
            QPixmap(":/numbers/realnixie_numbers/rn2.png"),
            QPixmap(":/numbers/realnixie_numbers/rn3.png"),
            QPixmap(":/numbers/realnixie_numbers/rn4.png"),
            QPixmap(":/numbers/realnixie_numbers/rn5.png"),
            QPixmap(":/numbers/realnixie_numbers/rn6.png"),
            QPixmap(":/numbers/realnixie_numbers/rn7.png"),
            QPixmap(":/numbers/realnixie_numbers/rn8.png"),
            QPixmap(":/numbers/realnixie_numbers/rn9.png")
    };


    int segment_;                   // To store the number of installed segments
    int value_;                     // For the value currently shown on the display
    int crushing_number_;           // To store the received value from display()
    int width_;                     // To store the length of one segment
    int height_;                    // For storing the height of one segment

    std::vector<int> number;        // For storing already split values

private slots:

void paintEvent(QPaintEvent *) override;        // Overridden method
int split(int number);                          // Splitting the resulting number

};
#endif // QNIXIENUMBER_H
