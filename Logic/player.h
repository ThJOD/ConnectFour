#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QObject>
#include "GUI/chip.h"

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QString name);

    virtual bool isHumanPlayer() = 0;
    virtual void requestMove(QVector<QVector<ChipColor>>& field) = 0;
    virtual void endGame(QString reason) = 0;
    virtual QString getName() = 0;

signals:
    void surrender();
    void madeMove(ChipColor color, int column);
    void ready(); //should be emmited shortly after initialization, game won't start until then

private:
    ChipColor color;
};

#endif // PLAYER_H
