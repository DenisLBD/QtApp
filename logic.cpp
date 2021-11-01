#include "logic.h"
#include <string>

Coordinates::Coordinates (QString str)
{
   coord = str;
   x_coord = "";
   y_coord = "";
}

bool Coordinates::CheckCoord()
{
    int i = 0;

    while (coord[i].isDigit())
    {
        x_coord.push_back(coord[i]);
        i++;
        if (coord.length() == i)
            return false;
    }

    if (x_coord == "")
        return false;

    if (coord[i] != ',')
        return false;

    i++;

    if (coord.length() == i)
        return false;

    while (coord[i].isDigit())
    {
        y_coord.push_back(coord[i]);
        i++;
        if (coord.length() == i)
            break;
    }

    if (y_coord == "")
        return false;

    if (i != coord.length())
        return false;

    return true;
}
