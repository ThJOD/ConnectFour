#include "gamehandler.h"

GameHandler::GameHandler(Player *firstPlayer, Player *secondPlayer, QObject *parent) :
    player1(firstPlayer), player2(secondPlayer)
{
    //initialize empty field with 7 columns and 6 rows
    field = QVector<QVector<ChipColor> >(6, QVector<ChipColor>(7, ChipColor::noColor));

    //start the game with player 1
    status = Status::turn_player1;

    moveTimer = nullptr;
}

void GameHandler::startGame()
{

}

void GameHandler::makeMove(ChipColor color, int column)
{

}
