#include "chip.h"

#include <QPainter>

Chip::Chip(ChipColor color, QWidget *parent) : QLabel()
{
    QPixmap pixmap;
    if(color == ChipColor::red)
        pixmap = QPixmap("textures/redChip.jpg");
    else if(color == ChipColor::yellow)
        pixmap = QPixmap("textures/yellowChip.jpg");

    this->setPixmap(pixmap);
}

ChipColor Chip::getColor()
{
    return color;
}
