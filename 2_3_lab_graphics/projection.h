#ifndef PROJECTION_H
#define PROJECTION_H

#include <QWidget>
#include <QTimer>
#include "figure.h"

class Projection : public QWidget
{
    Q_OBJECT
public:
    Projection();
    ~Projection() { delete timer; }

    QTimer *timer;
    Point3D centerPensil;
    Figure pensil;
    Point3D pointOfView;
    Matrix matrix;

public slots:
    void startRotate();
    void reset();
private slots:
    void rotateByX();
    void rotateByY();
    void rotateByZ();
    void resetMatrix();
    void setPensil();
    void paintEvent(QPaintEvent *event);
};

#endif // PROJECTION_H
