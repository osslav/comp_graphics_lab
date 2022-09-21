#include "MyRect.h"
#include <QtMath>

MyRect::MyRect(QPoint x0, qreal alpha, int length, int height)
{
    startPoly[0] = x0;

    startPoly[1].setX(x0.x() + sin(alpha)*length);
    startPoly[1].setY(x0.y() - cos(alpha)*length);

    startPoly[2].setX(startPoly[1].x() + cos(alpha)*height);
    startPoly[2].setY(startPoly[1].y() + sin(alpha)*height);

    startPoly[3].setX(x0.x() + cos(alpha)*height);
    startPoly[3].setY(x0.y() + sin(alpha)*height);

    currentPoly = startPoly;
}

QPolygon MyRect::getPolygon()
{
    return currentPoly;
}

void MyRect::mapPolygon(QMatrix matrix)
{
    currentPoly = matrix.map(startPoly);
}

QPoint MyRect::getAxisPoint()
{
    return currentPoly[currentAxisPoint];
}

void MyRect::nextAxisPoint()
{
    if (currentAxisPoint != 0)
        currentAxisPoint--;
    else
        currentAxisPoint = 3;
}

QLine MyRect::getMarkedLine()
{
    return QLine(currentPoly[0], currentPoly[1]);
}

int MyRect::maxX()
{
    int max = currentPoly[0].x();
    for(int i = 1; i < 4; i++)
        if (max < currentPoly[i].x())
            max = currentPoly[i].x();

    return max;
}

int MyRect::minX()
{
    int min = currentPoly[0].x();
    for(int i = 1; i < 4; i++)
        if (min > currentPoly[i].x())
            min = currentPoly[i].x();

    return min;
}

int MyRect::maxY()
{
    int max = currentPoly[0].y();
    for(int i = 1; i < 4; i++)
        if (max < currentPoly[i].y())
            max = currentPoly[i].y();

    return max;
}

int MyRect::minY()
{
    int min = currentPoly[0].y();
    for(int i = 1; i < 4; i++)
        if (min > currentPoly[i].y())
            min = currentPoly[i].y();

    return min;
}
