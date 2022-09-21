#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include "projection.h"

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);

    QVBoxLayout *generalVLayout;
    QHBoxLayout *buttonHLayout;

    QPushButton *startButton;
    QPushButton *resetButton;

    Projection *myProjection;
};
#endif // MYWIDGET_H
