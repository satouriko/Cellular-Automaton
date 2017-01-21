//
// Created by lijiahao on 9/10/16.
//

#include "gamecontroller.h"
#include "cellcar.h"
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

const double CellCar::getSpeed() const {
    return speed;
}

CellCar::CellCar(int x, int y) : Cell(x, y) {
    const int MAXSPEED = 5, MINSPEED = 1;
    speed = rand() % (MAXSPEED + 1 - MINSPEED) + MINSPEED;
    _dir = FORWARD;
}

void CellCar::moveOn(vector<CellCar>::iterator begin, vector<CellCar>::iterator end,
                     vector<CellCar>::iterator oldbegin, vector<CellCar>::iterator oldend) {
    syncSpeed(begin, end, oldbegin, oldend);
    if (_dir == FORWARD) {
        y += speed / FPS;
    } else if (_dir == BACK) {
        y -= speed / FPS;
    } else if (_dir == LEFT) {
        x += speed / FPS;
    } else if (_dir == RIGHT) {
        x -= speed / FPS;
    }
}

//void CellCar::turn(int direction) {
//    if (direction == LEFT)
//        ++_dir;
//    else if (direction == RIGHT)
//        --_dir;
//    if (_dir == -1)
//        _dir = 3;
//    if (_dir == 4)
//        _dir = 0;
//}

void CellCar::syncSpeed(vector<CellCar>::iterator begin, vector<CellCar>::iterator end,
                        vector<CellCar>::iterator oldbegin, vector<CellCar>::iterator oldend) {
    switch (_dir) {
    case FORWARD: {
        vector<CellCar>::iterator fnst = oldend;
        for(vector<CellCar>::iterator iter = oldbegin; iter != oldend; ++iter) {
            if(iter->getX() == x && iter->getY() > y) {
                if(fnst == oldend)
                    fnst = iter;
                else if(iter->getY() < fnst->getY())
                    fnst = iter;
            }
        }
        if(fnst != oldend && fnst->getY() - y < SAFEGAP)
            speed = fnst->getSpeed();
        else
            speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
    }
        break;

    case BACK: {
        vector<CellCar>::iterator fnst = oldend;
        for(vector<CellCar>::iterator iter = oldbegin; iter != oldend; ++iter) {
            if(iter->getX() == x && iter->getY() < y) {
                if(fnst == oldend)
                    fnst = iter;
                else if(iter->getY() > fnst->getY())
                    fnst = iter;
            }
        }
        if(fnst != oldend && y - fnst->getY() < SAFEGAP)
            speed = fnst->getSpeed();
        else
            speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
    }

    case LEFT: {
    }
        break;

    case RIGHT:{
    }
        break;
    }
}

//void CellCar::turn() {
//    bool flag = rand() % 2;
//    if (flag)
//        turn(LEFT);
//    else
//        turn(RIGHT);
//}
