#ifndef FIGURE_H
#define FIGURE_H

#include "point3d.h"
#include "matrix.h"

class Figure
{
private:
    int countPoints = 0;
    Point3D* arrPoints = nullptr;
    bool** matrixLines = nullptr;
    bool** matrixViewedLines = nullptr;

public:
    Figure() {};
    Figure(int countPoints_);
    ~Figure();

    int getCountPoints() { return countPoints; }

    void setPoint(int index, Point3D newPoint);
    Point3D getPoint(int index);

    void connectPoint(int indexFirstPoint, int indexSecondPoint);
    void disconnectPoint(int indexFirstPoint, int indexSecondPoint);
    bool checkLine(int indexFirstPoint, int indexSecondPoint);
    bool checkViewedLine(int indexFirstPoint, int indexSecondPoint);

    void calculateViewedLine(Point3D point_of_view);

    void changeFigure(Matrix matrix);

    void operator =(const Figure& temp);
    Point3D operator [](int index) { return arrPoints[index]; }
};

#endif // FIGURE_H
