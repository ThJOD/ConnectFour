#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "player.h"


/**
 * @brief The GameHandler class is the main controller of a game. It handles the interaction
 * between the players, ensures that the rules are being followed and provides the game flow.
 */
class GameHandler : public QObject
{
    Q_OBJECT

    enum class Status { turn_player1, turn_player2, finished };
public:
    GameHandler(Player* firstPlayer, Player* secondPlayer, QObject *parent = 0);
    void startGame();

signals:
    void playerMadeMove(ChipColor color, int column);

public slots:
    void makeMove(ChipColor color, int column);

private:
    Player *player1, *player2;
    QVector<QVector<ChipColor> > field; //field representation in row x column format

    Status status;
    QTimer *moveTimer; //this timer is used to check if a player is over his time limit
};

#endif // GAMEHANDLER_H
