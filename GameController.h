//
// Created by lijiahao on 9/10/16.
//

#ifndef CA_GAMECONTROLLER_H
#define CA_GAMECONTROLLER_H

#include "CellCar.h"
#include <vector>

#define CARNUM 100
#define LEFTXLIM 1
#define RIGHTXLIM 3
#define TOPYLIM 1
#define BOTTOMYLIM 100

void loop(std::vector<CellCar>&);
void draw(std::vector<CellCar>&);
std::vector<CellCar> createMap();

#endif //CA_GAMECONTROLLER_H
