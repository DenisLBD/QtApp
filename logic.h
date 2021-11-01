#pragma once

#include <QString>

class Coordinates
{
private:
    QString coord;
    QString x_coord;
    QString y_coord;

public:
    Coordinates(QString str);
    bool CheckCoord();

};

