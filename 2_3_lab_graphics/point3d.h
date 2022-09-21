#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{
private:
    int x = 0;
    int y = 0;
    int z = 0;

public:
    Point3D() {};
    Point3D(int x_, int y_, int z_);

    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }

    void shiftByX(int shift);
    void shiftByY(int shift);
    void shiftByZ(int shift);

    Point3D operator =(const Point3D& newPoint);
};


#endif // POINT3D_H
