#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QObject>

enum class ChipColor { yellow, red, noColor };

class Player : public QObject
{
    Q_OBJECT
public:
    Player();

    virtual bool isHumanPlayer() = 0;
    virtual void requestMove(QVector<QVector<ChipColor>>& field) = 0;
    virtual QString getName() = 0;

signals:
    void madeMove(ChipColor color, int column);

private:
    ChipColor color;
};

#endif // PLAYER_H
