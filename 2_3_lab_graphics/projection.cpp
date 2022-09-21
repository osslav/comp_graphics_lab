#include "projection.h"
#include <QPainter>

Projection::Projection()
{
    setMinimumSize(1280, 720);
    setMaximumSize(1280, 720);

    setPensil();
    resetMatrix();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateByY()));
}

void Projection::startRotate()
{
    timer->start(10);
}

void Projection::reset()
{
    if(timer->isActive())
        timer->stop();

    resetMatrix();
}

void Projection::rotateByX()
{
    //resetMatrix();
    matrix.shift(-centerPensil.getX(), -centerPensil.getY(), -centerPensil.getZ());
    matrix.rotateByX(3.14/(2*200));
    matrix.shift(centerPensil.getX(), centerPensil.getY(), centerPensil.getZ());

    //pensil.changeFigure(matrix);

    update();
}

void Projection::rotateByY()
{
    //resetMatrix();
    matrix.shift(-centerPensil.getX(), -centerPensil.getY(), -centerPensil.getZ());
    matrix.rotateByY(3.14/(2*200));
    matrix.shift(centerPensil.getX(), centerPensil.getY(), centerPensil.getZ());

    //pensil.changeFigure(matrix);

    update();
}

void Projection::rotateByZ()
{
    //resetMatrix();
    matrix.shift(-centerPensil.getX(), -centerPensil.getY(), -centerPensil.getZ());
    matrix.rotateByZ(3.14/(2*200));
    matrix.shift(centerPensil.getX(), centerPensil.getY(), centerPensil.getZ());

    //pensil.changeFigure(matrix);

    update();
}

void Projection::setPensil()
{
    centerPensil = Point3D(40, 0, 0);

    pensil = Figure(13);

    //задняя грань карандаша
    pensil.setPoint(0, Point3D(0,-4,-6));
    pensil.setPoint(1, Point3D(0,4,-6));
    pensil.setPoint(2, Point3D(0,8,0));
    pensil.setPoint(3, Point3D(0,4,6));
    pensil.setPoint(4, Point3D(0,-4,6));
    pensil.setPoint(5, Point3D(0,-8,0));

    //соединяем линиями задний 6-угольник
    for(int i = 1; i < 6; i++)
        pensil.connectPoint(i-1, i);
    pensil.connectPoint(0, 5);

    //передняя грань карандаша
    for(int i = 0; i < 6; i++)
    {
        Point3D newPoint = pensil.getPoint(i);
        newPoint.shiftByX(64);
        pensil.setPoint(i+6, newPoint);
    }

    //соединяем линиями передний 6-угольник
    for(int i = 7; i < 12; i++)
        pensil.connectPoint(i-1, i);
    pensil.connectPoint(6, 11);

    //соединяем линиями соответствующие вершины 6-угольников
    for(int i = 0; i < 6; i++)
        pensil.connectPoint(i, i+6);

    //делаем вершину кончика карандаша
    pensil.setPoint(12, Point3D(80,0,0));
    for(int i = 6; i < 12; i++)
        pensil.connectPoint(i, 12);


    //точка зрения
    pointOfView = Point3D(80,0,0);
}

void Projection::resetMatrix()
{
    matrix.reset();

    update();
}

void Projection::paintEvent(QPaintEvent *event)
{
    Figure Figure2D;
    Figure2D = pensil;
    Figure2D.changeFigure(matrix);

    Figure2D.calculateViewedLine(Point3D(0, 0, 100));

    Matrix matrix2D;
    matrix2D.shift(-pointOfView.getX(), -pointOfView.getY(), -pointOfView.getZ());
    matrix2D.scale(5, 5, 5);
    matrix2D.shift(1280/2, 720/2, 0);

    Figure2D.changeFigure(matrix2D);


    QPainter painter(this);

    for (int i = 0; i < Figure2D.getCountPoints(); i++)
        for (int j = i + 1; j < Figure2D.getCountPoints(); j++)
            if (Figure2D.checkLine(i, j))
            {   if(Figure2D.checkViewedLine(i, j))
                {
                    painter.setPen(QPen(QBrush(Qt::blue), 3));
                    painter.drawLine(QLine(QPoint(Figure2D[i].getX(), Figure2D[i].getY()), QPoint(Figure2D[j].getX(), Figure2D[j].getY())));
                }
                else
                    painter.setPen(QPen(QBrush(Qt::red), 1));
                //painter.drawLine(QLine(QPoint(Figure2D[i].getX(), Figure2D[i].getY()), QPoint(Figure2D[j].getX(), Figure2D[j].getY())));
            }
            else
            {
                if (Figure2D.checkViewedLine(i, j))
                {
                    painter.setPen(QPen(QBrush(Qt::darkBlue), 3));
                    painter.drawLine(QLine(QPoint(Figure2D[i].getX(), Figure2D[i].getY()), QPoint(Figure2D[j].getX(), Figure2D[j].getY())));
                }

            }
/*
    painter.setPen(QPen(QBrush(Qt::black), 4));

    for (int i = 0; i < Figure2D.getCountPoints(); i++)
            painter.drawPoint(QPoint(Figure2D[i].getX(), Figure2D[i].getY()));*/
}

