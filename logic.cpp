#include "logic.h"
#include <QList>

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

void Coordinates::removeCoords(QList<std::pair<int, int>> &listOfCoord)
{
    bool flag = false; //лежит ли точка на прямой
    double k = INT32_MAX;
    auto iter2 = listOfCoord.begin();
    ++iter2;

    for (auto iter1 = listOfCoord.begin(); iter2 != listOfCoord.end(); ++iter1)
    {
        if (std::abs(k - (iter1->second - iter2->second)*1.0/(iter1->first - iter2->first)) < 0.00001)
            flag = true;
        else
            flag = false;

        if (!flag)
        {
            k = (iter1->second - iter2->second)*1.0/(iter1->first - iter2->first);
            ++iter2;
        }
        else
        {
            listOfCoord.removeAt(listOfCoord.indexOf(iter1));
            iter1 = iter2;
            ++iter2;
        }
    }
}
