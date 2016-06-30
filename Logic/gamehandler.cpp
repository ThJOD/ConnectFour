#include "gamehandler.h"

/**
 * @brief GameHandler::GameHandler This constructor initializes a new game between player 1 and player 2
 * @param firstPlayer
 * @param secondPlayer
 * @param parent
 */
GameHandler::GameHandler(Player *firstPlayer, Player *secondPlayer, QObject *parent) :
    player1(firstPlayer), player2(secondPlayer)
{
    //initialize empty field with 7 columns and 6 rows
    field = QVector<QVector<ChipColor> >(nColumns, QVector<ChipColor>(nRows, ChipColor::noColor));

    //start the game with player 1
    status = Status::turn_player1;

    //initialize the timer as a singleshot timer with the interval time set to the time for a move
    moveTimer = new QTimer;
    moveTimer->setInterval(moveTime);
    moveTimer->setSingleShot(true);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(handleTimerTimeout()));
}

/**
 * @brief GameHandler::startGame starts the game after the GameHandler object has been initialized
 */
void GameHandler::startGame()
{
    player1->requestMove(field);
    if(!player1->isHumanPlayer()){
        moveTimer->start();
    }
}

/**
 * @brief GameHandler::makeMove reacts to the move a player. This slot should be called by one of the
 * participants. It checks if the move is correct and reacts appropriatly
 * @param color the color of the player who made the move
 * @param column the column into which the player wants to place his chip
 */
void GameHandler::makeMove(ChipColor color, int column)
{
    //stop timer when still active
    if(moveTimer->isActive())
        moveTimer->stop();

    //return if player answer came too late
    if(status == Status::player1_timeout || status == Status::player2_timeout)
        return;

    //Check if it's the players turn
    if(status == Status::turn_player1 && color != ChipColor::red){
        status = Status::player2_wrong_timing;
        endGame();
        return;
    }

    if(status == Status::turn_player2 && color != ChipColor::yellow){
        status = Status::player1_wrong_timing;
        endGame();
        return;
    }

    //Check if it's a correct move (boundries correct and there is space in the selected column)
    if(column < 0 || column > nColumns - 1 || field[column][nRows - 1] != ChipColor::noColor){
        if(status == Status::turn_player1)
            status = Status::player1_bad_turn;
        else
            status = Status::player2_bad_turn;
        endGame();
        return;
    }

    //place the new chip on the field
    for(ChipColor chip : field[column]){
        //iterate from bottom to top of the column and find the first empty spot
        if(chip == ChipColor::noColor)
            chip = color;
    }

    //Check if player has won
    if(playerWon(column)){
        if(status == Status::turn_player1)
            status = Status::player1_won;
        if(status == Status::turn_player2)
            status = Status::player2_won;
        endGame();
        return;
    }

    //request next move from other player and start timer if neccessary
    if(status == Status::turn_player1){
        player2->requestMove(field);
        if(!player2->isHumanPlayer())
            moveTimer->start();
    } else if(status == Status::turn_player2){
        player1->requestMove(field);
        if(!player1->isHumanPlayer())
            moveTimer->start();
    }

    //emit signal to notify connected objects (for example gui)
    emit playerMadeMove(color, column);
}

/**
 * @brief GameHandler::handleTimerTimeout is called when the Timer set up for the current move is over.
 * It then determines whose move it was and ends the game accordingly.
 */
void GameHandler::handleTimerTimeout()
{
    if(status == Status::turn_player1)
        status = Status::player1_timeout;
    else if (status == Status::turn_player2)
        status = Status::player2_timeout;
    endGame();
}

/**
 * @brief GameHandler::playerWon checks if the player who made the last move has won the game
 * @param column The index of the column of the last move from the current player
 * @return true if the player won after the last move
 */
bool GameHandler::playerWon(int column)
{
    //the last chip in the specified column should be the one inserted from the current player
    //first find that and then check in every direction for other chips

    int row;
    ChipColor color;
    for(int i = nRows; i >= 0; --i){
        if(field[column][i] != ChipColor::noColor){
            row = i;
            color = field[column][i];
            break;
        }
    }
    /****horizontal*****/
    int nChips = 1;
    //horizontal line to the left
    for(int i = column - 1; i >= 0 && column - i < 4; --i){
        if(field[i][row] == color)
            ++nChips;
        else
            break;
    }
    //horizontal line to the right
    for(int i = column + 1; i < nColumns && i - column < 4; ++i){
        if(field[i][row] == color)
            ++nChips;
        else
            break;
    }
    if(nChips >= 4){
        return true;
    }


    /*****vertical*******/
    nChips = 0;
    //vertical line down
    for(int i = row - 1; i >= 0 && row - i < 4; --i){
        if(field[column][i] == color)
            ++nChips;
        else
            break;
    }
    //vertical line up
    for(int i = row + 1; i < nRows && i - row < 4; ++i){
        if(field[column][i] == color)
            ++nChips;
        else
            break;
    }
    if(nChips >= 4){
        return true;
    }


    /****diagonal top left to bottom right *****/
    nChips = 0;
    // to top left
    for(int i = 1; i < 4 && row + i < nRows && column - i >= 0; ++i){
        if(field[column - i][row + i] == color)
            ++nChips;
        else
            break;
    }
    //to bottom right
    for(int i = 1; i < 4 && row - i >= 0 && column + i < nColumns; ++i){
        if(field[column + i][row - i] == color)
            ++nChips;
        else
            break;
    }
    if(nChips >= 4){
        return true;
    }


    /****diagonal bottom left to top right *****/
    nChips = 0;
    // to top right
    for(int i = 1; i < 4 && row + i < nRows && column + i < nColumns; ++i){
        if(field[column + i][row + i] == color)
            ++nChips;
        else
            break;
    }
    //to bottom left
    for(int i = 1; i < 4 && row - i >= 0 && column - i >= 0; ++i){
        if(field[column - i][row - i] == color)
            ++nChips;
        else
            break;
    }
    if(nChips >= 4){
        return true;
    }



    return false;
}

/**
 * @brief GameHandler::endGame is called when the game is over. It determines the reason and emits gameOver() with
 * a message describing the reason
 */
void GameHandler::endGame()
{
    QString player1Name = player1->getName();
    QString player2Name = player2->getName();
    switch(status){
    case Status::player1_bad_turn:
        emit gameOver(player1Name + " (Player 1) made an illegal move");
        break;
    case Status::player2_bad_turn:
        emit gameOver(player2Name + " (Player 2) made an illegal move");
        break;
    case Status::player1_surrendered:
        emit gameOver(player1Name + " (Player 1) surrendered");
        break;
    case Status::player2_surrendered:
        emit gameOver(player2Name + " (Player 2) surrendered");
        break;
    case Status::player1_timeout:
        emit gameOver(player1Name + "(Player1) didn't respond in time");
        break;
    case Status::player2_timeout:
        emit gameOver(player2Name + "(Player2) didn't respond in time");
        break;
    case Status::player1_won:
        emit gameOver(player1Name + "(Player1) won!");
        break;
    case Status::player2_won:
        emit gameOver(player2Name + "(Player2) won!");
        break;
    case Status::player1_wrong_timing:
        emit gameOver(player1Name + "(Player1) tried to play, even though it's not his turn");
        break;
    case Status::player2_wrong_timing:
        emit gameOver(player2Name + "(Player2) tried to play, even though it's not his turn");
        break;
    default:
        emit gameOver("game over for unknown reason");
    }
}
