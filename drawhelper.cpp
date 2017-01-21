#include "gamecontroller.h"
#include "drawhelper.h"

using namespace std;

DrawHelper::DrawHelper() {}

void DrawHelper::drawCars(vector<CellCar> &cars)
{
    for(vector<CellCar>::iterator iter = cars.begin(); iter != cars.end(); ++iter) {
        drawCar(*iter);
    }
}

void DrawHelper::drawBlocks(std::vector<CellBlock> &blocks)
{
    for(vector<CellBlock>::iterator iter = blocks.begin(); iter != blocks.end(); ++iter) {
        drawBlock(*iter);
    }
}

void DrawHelper::syncPainter(QPainter *painter)
{
    this->painter = painter;
}

void DrawHelper::clc()
{
    this->painter->setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap));
    this->painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    this->painter->drawRect(0, 0, SIZE * RIGHTXLIM, SIZE * BOTTOMYLIM);
}

void DrawHelper::drawCar(CellCar &car)
{
    this->painter->setRenderHint(QPainter::Antialiasing, true);
    this->painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    this->painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->painter->drawRect((int)(car.getX() * SIZE), (int)(car.getY() * SIZE), SIZE, SIZE);
}

void DrawHelper::drawBlock(CellBlock &block)
{
    this->painter->setRenderHint(QPainter::Antialiasing, true);
    this->painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap));
    this->painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    QRectF rect((int)(block.getX() * SIZE), (int)(block.getY() * SIZE), SIZE, SIZE);
    this->painter->drawRect(rect);
    this->painter->setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap));
    char text[] = {  block.getType(), '\0' };
    this->painter->drawText(rect, Qt::AlignHCenter, text);
}
