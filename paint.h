#pragma once

#include <QPainter>
#include <QList>
#include <QFrame>

class Frame : public QFrame
{

Q_OBJECT

public:
    Frame(QList<std::pair<int, int>> listOfCoord, QWidget *parent = 0);

public:
    void paintEvent(QPaintEvent *e);
    void drawLines();

private:
    QList<std::pair<int, int>> CoordList;
};
