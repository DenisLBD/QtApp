#pragma once

#include <QString>
#include <QList>

class Coordinates
{
private:
    QString coord;
    QString x_coord;
    QString y_coord;

public:
    Coordinates(QString str);
    bool CheckCoord();
    std::pair<int, int> GetCoord();
    void removeCoords (QList<std::pair<int, int>>& listOfCoord);

};

