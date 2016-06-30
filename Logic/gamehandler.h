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

    enum class Status { turn_player1,
                        turn_player2,
                        player1_surrendered,
                        player2_surrendered,
                        player1_timeout,
                        player2_timeout,
                        player1_bad_turn,
                        player2_bad_turn,
                        player1_wrong_timing,
                        player2_wrong_timing,
                        player1_won,
                        player2_won
                        };
public:
    GameHandler(Player* firstPlayer, Player* secondPlayer, QObject *parent = 0);
    void startGame();

signals:
    void playerMadeMove(ChipColor color, int column);
    void gameOver(QString message);

public slots:
    void makeMove(ChipColor color, int column);

private slots:
    void handleTimerTimeout();

private:
    bool playerWon(int column);
    void endGame();

    Player *player1, *player2;
    QVector<QVector<ChipColor> > field; //field representation in column x row format (first entry in column is bottom line)
    QTimer *moveTimer; //this timer is used to check if a player is over his time limit

    Status status;

    //Constants
    const int moveTime = 2000; //time a player has to make his move
    const int nRows = 6;
    const int nColumns = 7;
};

#endif // GAMEHANDLER_H
