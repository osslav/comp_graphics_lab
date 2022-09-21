#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    myAnimation = new Animation();

    generalVLayout = new QVBoxLayout();
    buttonHLayout = new QHBoxLayout();

    startButton = new QPushButton("start");
    resetRectButton = new QPushButton("reset rect");
    resetLineButton = new QPushButton("reset line");

    buttonHLayout->addWidget(startButton);
    buttonHLayout->addWidget(resetRectButton);
    buttonHLayout->addWidget(resetLineButton);

    generalVLayout->addWidget(myAnimation);
    generalVLayout->addLayout(buttonHLayout);

    setLayout(generalVLayout);

    connect(startButton, SIGNAL(clicked()), myAnimation, SLOT(start()));
    connect(resetRectButton, SIGNAL(clicked()), myAnimation, SLOT(resetRect()));
    connect(resetLineButton, SIGNAL(clicked()), myAnimation, SLOT(resetLine()));
}


