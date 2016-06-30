#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "GUI/chip.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();

public slots:
    void insertChip(ChipColor color, int column);
    void requestMove(ChipColor color);

signals:
    void madeMove(ChipColor color, int column);
};

#endif // GAMEWINDOW_H
