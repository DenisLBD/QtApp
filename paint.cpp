#include <QPainter>
#include <QList>
#include "paint.h"

Frame::Frame(QList<std::pair<int, int>> listOfCoord, QWidget *parent) : QFrame(parent)
{
    CoordList = listOfCoord;
}

void Frame::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    drawLines();
}

void Frame::drawLines ()
{
    QPainter qp(this);
    QPen pen (Qt::black, 1, Qt::SolidLine);
    qp.setPen(pen);

    auto iter2 = CoordList.begin();
    ++iter2;

    for (auto iter1 = CoordList.begin(); iter2 != CoordList.end(); ++iter1)
    {
        qp.drawLine(iter1->first, iter1->second, iter2->first, iter2->second);
        ++iter2;
    }
}
