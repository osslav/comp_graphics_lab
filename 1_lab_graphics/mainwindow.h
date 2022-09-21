#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include "Animation.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QVBoxLayout *generalVLayout;
    QHBoxLayout *buttonHLayout;

    QPushButton *startButton;
    QPushButton *resetRectButton;
    QPushButton *resetLineButton;

    Animation *myAnimation;
};
#endif // MAINWINDOW_H
