#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    myProjection = new Projection();

    generalVLayout = new QVBoxLayout();
    buttonHLayout = new QHBoxLayout();

    startButton = new QPushButton("start");
    resetButton = new QPushButton("reset");

    buttonHLayout->addWidget(startButton);
    buttonHLayout->addWidget(resetButton);

    generalVLayout->addWidget(myProjection);
    generalVLayout->addLayout(buttonHLayout);

    setLayout(generalVLayout);

    connect(startButton, SIGNAL(clicked()), myProjection, SLOT(startRotate()));
    connect(resetButton, SIGNAL(clicked()), myProjection, SLOT(reset()));
}


