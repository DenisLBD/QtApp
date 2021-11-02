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

    x_coord = "";
    y_coord = "";

    return true;
}

std::pair<int, int> Coordinates::GetCoord()
{
    int i = 0;
    while (coord[i].isDigit())
    {
        x_coord.push_back(coord[i]);
        i++;
    }

    i++;

    while (coord[i].isDigit())
    {
        y_coord.push_back(coord[i]);
        i++;
        if (coord.length() == i)
            break;
    }

    int intXc = x_coord.toInt();
    int intYc = y_coord.toInt();

    std::pair<int, int> pair;

    pair = std::make_pair(intXc, intYc);

    return pair;
}
