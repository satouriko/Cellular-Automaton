#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include <QPainter>
#include "cellcar.h"
#include "cellblock.h"
#include "carfactory.h"
#include "carcollector.h"
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
    void drawCarCollectors(std::vector<CarCollector> &ccs);
    void syncPainter(QPainter *painter);
private:
    QPainter *painter;
    void drawCar(CellCar &car);
    void drawBlock(CellBlock &block);
    void drawCarFactory(CarFactory &cf);
    void drawCarCollector(CarCollector &cc);
};

#endif // DRAWHELPER_H
