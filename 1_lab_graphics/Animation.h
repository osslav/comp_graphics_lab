#ifndef ANIMATION_H
#define ANIMATION_H

#include "MyRect.h"
#include <QWidget>
#include <QRect>
#include <QTimer>

class Animation : public QWidget
{
    Q_OBJECT
public:
    Animation();
    virtual ~Animation() { delete timer; };

public slots:
    void resetRect();
    void start();
    void resetLine();

private slots:
    void paintEvent(QPaintEvent *event);
    void newFrame();

private:
    void newMatrix();
    int remainderFrameInCurrentFlip = 0;
    const int frameInOneFlip = 30;
    const int flipInOneSecond = 2;

    MyRect rect;
    QLine line;
    QMatrix matrix;

    QTimer *timer;
};

#endif // ANIMATION_H
