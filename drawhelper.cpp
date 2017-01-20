#include "drawhelper.h"
#include "GameController.h"

using namespace std;

DrawHelper::DrawHelper() {}

void DrawHelper::drawCars(vector<CellCar> &cars)
{
    for(vector<CellCar>::iterator iter = cars.begin(); iter != cars.end(); ++iter) {
        drawCar(*iter);
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
    this->painter->drawRect(0, 0, 10 * RIGHTXLIM, 10 * BOTTOMYLIM);
}

void DrawHelper::drawCar(CellCar &car)
{
    this->painter->setRenderHint(QPainter::Antialiasing, true);
    this->painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    this->painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->painter->drawRect((int)(car.getX() * 10), (int)(car.getY() * 10), 10, 10);
}
