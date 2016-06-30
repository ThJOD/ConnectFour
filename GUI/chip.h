#ifndef CHIP_H
#define CHIP_H

#include <QWidget>
#include <QLabel>

enum class ChipColor{red, yellow, noColor};

class Chip : public QLabel
{
    Q_OBJECT
public:
    Chip(ChipColor color, QWidget *parent = 0);

    ChipColor getColor();

private:
    ChipColor color;
};

#endif // CHIP_H
