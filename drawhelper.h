#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include <QPainter>
#include "cellcar.h"
#include "cellblock.h"
#include "carfactory.h"
#include <vector>

#define SIZE 20

class DrawHelper
{
public:
    DrawHelper();
    void clc();
    void drawCars(std::vector<CellCar> &cars);
    void drawBlocks(std::vector<CellBlock> &blocks);
    void drawCarFactories(std::vector<CarFactory> &cfs);
    void syncPainter(QPainter *painter);
private:
    QPainter *painter;
    void drawCar(CellCar &car);
    void drawBlock(CellBlock &block);
    void drawCarFactory(CarFactory &cf);
};

#endif // DRAWHELPER_H
