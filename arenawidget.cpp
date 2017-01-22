#include "arenawidget.h"
#include "ui_arenawidget.h"
#include <QPainter>
#include <iostream>

using namespace std;

ArenaWidget::ArenaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArenaWidget)
{
    ui->setupUi(this);
}

ArenaWidget::~ArenaWidget()
{
    delete ui;
}

void ArenaWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    emit onDraw(&painter);
}

void ArenaWidget::mousePressEvent(QMouseEvent *e)
{
    emit onPaintCellBlock(e->x() / 20, e->y() / 20);
}
