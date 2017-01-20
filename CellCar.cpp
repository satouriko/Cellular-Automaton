//
// Created by lijiahao on 9/10/16.
//

#include "GameController.h"
#include "CellCar.h"
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

const int CellCar::getX() const {
    return x;
}

const int CellCar::getY() const {
    return y;
}

CellCar::CellCar(int x, int y) : x(x), y(y) {
    const int MAXSPEED = 5, MINSPEED = 1;
    speed = rand() % (MAXSPEED + 1 - MINSPEED) + MINSPEED;
    _dir = FORWARD;
}

void CellCar::moveOn(vector<CellCar>::iterator begin, vector<CellCar>::iterator end) {
    syncSpeed(begin, end);
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

void CellCar::turn(int direction) {
    if (direction == LEFT)
        ++_dir;
    else if (direction == RIGHT)
        --_dir;
    if (_dir == -1)
        _dir = 3;
    if (_dir == 4)
        _dir = 0;
}

bool operator==(const CellCar &objstruct1, const CellCar &objstruct2)  //重载“==”操作符
{
    return fabs(objstruct1.getX() - objstruct2.getX()) <= 0 && objstruct1.getY() > objstruct2.getY() && objstruct1.getY() - objstruct2.getY() <= 1.0;//具体匹配条件自己设定，可以设定多个
}

void CellCar::syncSpeed(vector<CellCar>::iterator begin, vector<CellCar>::iterator end) {
    bool flag = false;
    CellCar *temp = 0;
    switch (_dir) {
        case FORWARD:
            for (int i = 1; i <= SAFEGAP; ++i) {
                temp = new CellCar(x, y + i - 0.5);
                vector<CellCar>::iterator it = find(begin, end, *temp);
                if(it != end && !(it->getX() == x && it->getY() == y)) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                speed = 0;
            else
                speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
            break;

        case BACK:
            bool flag;
            for (int i = 1; i <= SAFEGAP; ++i) {
                temp = new CellCar(x, y - i + 0.5);
                vector<CellCar>::iterator it = find(begin, end, *temp);
                if(it != end && !(it->getX() == x && it->getY() == y)) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                speed = 0;
            else
                speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
            break;

        case LEFT:
            for (int i = 1; i <= SAFEGAP; ++i) {
                temp = new CellCar(x + i - 0.5, y);
                vector<CellCar>::iterator it = find(begin, end, *temp);
                if(it != end && !(it->getX() == x && it->getY() == y)) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                speed = 0;
            else
                speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
            break;

        case RIGHT:
            for (int i = 1; i <= SAFEGAP; ++i) {
                temp = new CellCar(x - i + 0.5, y);
                vector<CellCar>::iterator it = find(begin, end, *temp);
                if(it != end && !(it->getX() == x && it->getY() == y)) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                speed = 0;
            else
                speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
            break;
    }
}

void CellCar::turn() {
    bool flag = rand() % 2;
    if (flag)
        turn(LEFT);
    else
        turn(RIGHT);
}
