//
// Created by lijiahao on 9/10/16.
//

#ifndef CA_CELLCAR_H
#define CA_CELLCAR_H

#define FORWARD 0
#define BACK 2
#define LEFT 1
#define RIGHT 3

#define SAFEGAP 2
#define SPEEDLIMIT 100
#define ACC 2.0

#include <vector>
#include "cell.h"

class CellCar : public Cell {
    double speed;
    int _dir;

    void turn(int direction);

public:
    CellCar(int x, int y);

    void moveOn(std::vector<CellCar>::iterator begin, std::vector<CellCar>::iterator end,
                std::vector<CellCar>::iterator oldbegin, std::vector<CellCar>::iterator oldend);

    void turn();

    const double getSpeed() const ;

    void syncSpeed(std::vector<CellCar>::iterator begin, std::vector<CellCar>::iterator end,
                   std::vector<CellCar>::iterator oldbegin, std::vector<CellCar>::iterator oldend);
};

#endif //CA_CELLCAR_H
