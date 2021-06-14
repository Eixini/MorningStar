#include "qnixienumber.h"

QNixieNumber::QNixieNumber(QWidget *parent, mode_ mode) : QWidget(parent)
{
    selectMode_ = mode;

    /*  Retrieving segment length and height values based on the selected style   */
    if(selectMode_ == NIXIE)
    {
        width_ = NixieNumber[0].width();
        height_ = NixieNumber[0].height();
    }
    if(selectMode_ == REALNIXIE)
    {
        width_ = RealNixieNumber[0].width();
        height_ = RealNixieNumber[0].height();
    }

}

void QNixieNumber::setStyle(mode_ mode) { selectMode_ = mode; }

int QNixieNumber::intValue() const {  return value_; }

void QNixieNumber::display(int num)
{
    crushing_number_ = value_ = num;

    for(int i = 0; i < segment_ ; ++i)                                    // Loop to split a number and write individual digits to an array
        number.push_back(split(crushing_number_));

    std::reverse(number.begin(),number.end());                            // To reverse values, since they were written in reverse order
}

void QNixieNumber::setSegmentsCount(int value) { segment_ = value; }     // Setting the number of segments

void QNixieNumber::paintEvent(QPaintEvent *)
{

    QPainter paint(this);
    QNixieNumber::update();                                      // Automatic redrawing

    /* Based on the selected style, images (numbers) are drawn from the array */
    if(selectMode_ == NIXIE)
        for(int i = 0; i < segment_ ; ++i)
            paint.drawPixmap(width_ * i,0, NixieNumber[number[i]]);

    if(selectMode_ == REALNIXIE)
        for(int i = 0; i < segment_ ; ++i)
            paint.drawPixmap(width_ * i,0, RealNixieNumber[number[i]]);


}

int QNixieNumber::split(int number)
{
    // Splitting a number
    int n = number % 10;
    crushing_number_ = (number - n) / 10;
    return n;
}

QNixieNumber::~QNixieNumber() {}
