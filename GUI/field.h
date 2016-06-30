#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include "chip.h"

class Field : public QWidget
{
    Q_OBJECT
    enum class ChipColor{yellow, red};
public:
    explicit Field(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:

private:
    QVector<QPair<QPoint, ChipColor>> chips;

    const int margin = 10;
    const int gridBorderSize = 3;
};

#endif // FIELD_H
