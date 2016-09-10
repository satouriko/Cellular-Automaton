//
// Created by lijiahao on 9/10/16.
//

#include "CellCar.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int CellCar::getX() const {
    return x;
}

const int CellCar::getY() const {
    return y;
}

CellCar::CellCar(int x, int y) : x(x), y(y) {
    srand((int) time(0));
    const int MAXSPEED = 5, MINSPEED = 1;
    speed = rand() % (MAXSPEED + 1 - MINSPEED) + MINSPEED;
    _dir = FORWARD;
}

void CellCar::moveOn(vector<CellCar>::iterator begin, vector<CellCar>::iterator end) {
    syncSpeed(begin, end);
    if (_dir == FORWARD) {
        y += speed;
    } else if (_dir == BACK) {
        y -= speed;
    } else if (_dir == LEFT) {
        x += speed;
    } else if (_dir == RIGHT) {
        x -= speed;
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
    return objstruct1.getX() == objstruct2.getX() && objstruct1.getY() == objstruct2.getY();//具体匹配条件自己设定，可以设定多个
}

void CellCar::syncSpeed(vector<CellCar>::iterator begin, vector<CellCar>::iterator end) {
    bool flag = true;
    CellCar *temp;
    switch (_dir) {
        case FORWARD:
            for (int i = 1; i <= SAFEGAP; ++i) {
                *temp = CellCar(x, y + i);
                flag &= find(begin, end, *temp) != end;
            }
            if (flag)
                speed = 0;
            else
                speed + ACC == SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC;
            break;

        case BACK:
            bool flag;
            for (int i = 1; i <= SAFEGAP; ++i) {
                *temp = CellCar(x, y - i);
                flag &= find(begin, end, *temp) != end;
            }
            if (flag)
                speed = 0;
            else
                speed + ACC == SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC;
            break;

        case LEFT:
            for (int i = 1; i <= SAFEGAP; ++i) {
                *temp = CellCar(x + i, y);
                flag &= find(begin, end, *temp) != end;
            }
            if (flag)
                speed = 0;
            else
                speed + ACC == SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC;
            break;

        case RIGHT:
            for (int i = 1; i <= SAFEGAP; ++i) {
                *temp = CellCar(x - i, y);
                flag &= find(begin, end, *temp) != end;
            }
            if (flag)
                speed = 0;
            else
                speed + ACC == SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC;
            break;
    }
}

void CellCar::turn() {
    srand((int) time(0));
    bool flag = rand() % 2;
    if (flag)
        turn(LEFT);
    else
        turn(RIGHT);
}
