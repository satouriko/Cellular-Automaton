#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include <QPainter>
#include "cellcar.h"
#include "cellblock.h"
#include <vector>

#define SIZE 10

class DrawHelper
{
public:
    DrawHelper();
    void clc();
    void drawCars(std::vector<CellCar> &cars);
    void drawBlocks(std::vector<CellBlock> &blocks);
    void syncPainter(QPainter *painter);
private:
    QPainter *painter;
    void drawCar(CellCar &car);
    void drawBlock(CellBlock &block);
};

#endif // DRAWHELPER_H
