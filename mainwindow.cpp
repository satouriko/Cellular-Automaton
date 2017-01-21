#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontroller.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->gc = new GameController();
    connect(ui->widget, SIGNAL(onDraw(QPainter*)), this->gc, SLOT(draw(QPainter*)));
    connect(this->gc, SIGNAL(onRedraw()), this, SLOT(redraw()));
    this->gc->startLooping();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redraw()
{
    ui->widget->repaint();
}
