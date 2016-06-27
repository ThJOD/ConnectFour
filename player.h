#ifndef PLAYER_H
#define PLAYER_H

enum class ChipColor { yellow, red, noColor };

class Player
{
public:
    Player();

    virtual bool isHumanPlayer() = 0;
    virtual void makeMove(QVector<QVector<ChipColor>>& field) = 0;

public slots:
    void madeMove(ChipColor color, int column);

private:
    ChipColor color;
};

#endif // PLAYER_H
