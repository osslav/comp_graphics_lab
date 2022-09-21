#include "Animation.h"
#include <QPainter>
#include <QtMath>

Animation::Animation()
{
    setMinimumSize(1280, 720);
    setMaximumSize(1280, 720);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newFrame()));

    resetLine();
}

void Animation::resetRect()
{
   qreal alpha = qAtan(qreal(line.dy())/qreal(line.dx()));
   rect = MyRect(line.p1(), alpha, 40, 80);

   remainderFrameInCurrentFlip = 0;
   if (timer && timer->isActive())
       timer->stop();

   matrix.reset();
   update();
}

void Animation::start()
{
    timer->start(1000/(frameInOneFlip*flipInOneSecond));   //one flip per second
}

void Animation::resetLine()
{
    line = QLine(20, rand() % size().height(), size().width(), rand() % size().height());
    resetRect();
}

void Animation::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush(Qt::black), 2));
    painter.drawLine(line);

    painter.setPen(QPen(QBrush(Qt::blue), 2));
    painter.setBrush(QBrush(QColor(Qt::cyan)));
    painter.drawPolygon(rect.getPolygon());

    painter.setPen(QPen(QBrush(Qt::red), 2));
    painter.drawLine(rect.getMarkedLine());
}

void Animation::newFrame()
{
    if (remainderFrameInCurrentFlip == 0)
    {
        remainderFrameInCurrentFlip = frameInOneFlip;
        rect.nextAxisPoint();
    }

    newMatrix();
    rect.mapPolygon(matrix);

    remainderFrameInCurrentFlip--;
    update();

    if (rect.maxX() > size().width() || rect.minY() < 0)
        timer->stop();
}

void Animation::newMatrix()
{
    QPoint axisPoint = rect.getAxisPoint();

    QMatrix newMove;
    newMove.translate(axisPoint.x(), axisPoint.y());
    newMove.rotate(qreal(90)/frameInOneFlip);
    newMove.translate(-axisPoint.x(), -axisPoint.y());

    matrix *= newMove;
}
