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
    if(e->button() == Qt::RightButton) {
        emit onPaintCell(e->x() / 20, e->y() / 20, false);
    }
    else
        emit onPaintCell(e->x() / 20, e->y() / 20, true);
}
