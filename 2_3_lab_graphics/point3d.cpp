#include "point3d.h"

Point3D::Point3D(int x_, int y_, int z_)
{
    x = x_;
    y = y_;
    z = z_;
}

void Point3D::shiftByX(int shift)
{
    x += shift;
}

void Point3D::shiftByY(int shift)
{
    y += shift;
}

void Point3D::shiftByZ(int shift)
{
    z += shift;
}


Point3D Point3D::operator =(const Point3D& newPoint)
{
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
}
