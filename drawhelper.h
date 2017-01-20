#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include <QPainter>
#include "CellCar.h"
#include <vector>

class DrawHelper
{
public:
    DrawHelper();
    void clc();
    void drawCars(std::vector<CellCar> &cars);
    void syncPainter(QPainter *painter);
private:
    QPainter *painter;
    void drawCar(CellCar &car);
};

#endif // DRAWHELPER_H
