#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

class GameWindow : public QWidget
{
public:
    GameWindow();

private:
    void redrawField();
};

#endif // GAMEWINDOW_H
