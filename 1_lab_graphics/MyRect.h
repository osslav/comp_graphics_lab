#ifndef MYRECT_H
#define MYRECT_H

#include <QPoint>
#include <QPolygon>
#include <QMatrix>
#include <QLine>

class MyRect
{
 private:
    QPolygon startPoly = QPolygon(4);
    QPolygon currentPoly = QPolygon(4);
    int currentAxisPoint = 0;

public:
    MyRect(QPoint x0 = QPoint(0,0), qreal alpha = 0, int length = 1, int height = 1);

    QPolygon getPolygon();
    void mapPolygon(QMatrix matrix);

    QPoint getAxisPoint();
    void nextAxisPoint();

    QLine getMarkedLine();

    int maxX();
    int minX();
    int maxY();
    int minY();
};

#endif // MYRECT_H
