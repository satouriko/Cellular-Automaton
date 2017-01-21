//
// Created by lijiahao on 9/10/16.
//

#include "gamecontroller.h"
#include "cellcar.h"
#include "cellblock.h"
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

CellCar::CellCar(int x, int y) : Cell(x, y), status(GOAHEAD), tgx(x), tgy(y) {
    const int MAXSPEED = 5, MINSPEED = 1;
    speed = rand() % (MAXSPEED + 1 - MINSPEED) + MINSPEED;
    _dir = FORWARD;
}

void CellCar::moveOn(vector<CellCar>::const_iterator oldbegin, vector<CellCar>::const_iterator oldend,
                     vector<CellBlock>::const_iterator cbbegin, vector<CellBlock>::const_iterator cbend) {
    syncSpeed(oldbegin, oldend, cbbegin, cbend);
    crab();
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

void CellCar::syncSpeed(vector<CellCar>::const_iterator oldbegin, vector<CellCar>::const_iterator oldend,
                        vector<CellBlock>::const_iterator cbbegin, vector<CellBlock>::const_iterator cbend) {
    switch (_dir) {
    case FORWARD: {
        vector<CellCar>::const_iterator fnst = oldend;
        int lcnt = 0, rcnt = 0, mcnt = 0;
        for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
            if(iter->getX() == x && iter->getY() > y) {
                if(iter->getY() - y <= CONGESTGAP)
                    ++mcnt;
                if(fnst == oldend)
                    fnst = iter;
                else if(iter->getY() < fnst->getY())
                    fnst = iter;
            }
            else if(iter->getX() == x + 1 && iter->getY() > y && iter->getY() - y <= CONGESTGAP)
                ++lcnt;
            else if(iter->getX() == x - 1 && iter->getY() > y && iter->getY() - y <= CONGESTGAP)
                ++rcnt;
        }
        if(fnst != oldend && fnst->getY() - y < SAFEGAP) {
            speed = fnst->getSpeed();
            if(this->status == GOAHEAD) {
                switch(lineJudge(cbbegin, cbend, lcnt, rcnt, mcnt)) {
                case GOLEFT:
                    //
                    this->tgx = x + 1;
                    this->status = GOLEFT;
                    break;
                case GORIGHT:
                    //
                    this->tgx = x - 1;
                    this->status = GORIGHT;
                }
            }
        }
        else
            speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
    }
        break;

    default :{
    }
        break;
    }
}

RelativeDir CellCar::lineJudge(vector<CellBlock>::const_iterator cbbegin, vector<CellBlock>::const_iterator cbend,
                               int lcnt, int rcnt, int mcnt)
{
    switch (_dir) {
    case FORWARD:
        for(vector<CellBlock>::const_iterator iter = cbbegin; iter != cbend; ++iter) {
            if(iter->getX() == x && iter->getY() > y && iter->getY() - y <= 1) {
                if(iter->getType() == 'L') return GOLEFT;
                else if(iter->getType() == 'R') return GORIGHT;
                else if(iter->getType() == '1') return GOAHEAD;
                else if(iter->getType() == '2') return lcnt < rcnt ? GOLEFT : GORIGHT;
                else if(iter->getType() == 'l') return lcnt < mcnt ? GOLEFT : GOAHEAD;
                else if(iter->getType() == 'r') return rcnt < mcnt ? GORIGHT : GOAHEAD;
            }
        }
        return lcnt < rcnt ? ( lcnt < mcnt ? GOLEFT : GOAHEAD ) : ( rcnt < mcnt ? GORIGHT : GOAHEAD );
    default:
        return GOAHEAD;
    }
}

void CellCar::crab()
{
    switch(_dir) {
    case FORWARD:
        switch(this->status) {
        case GOLEFT:
            x += speed / FPS;
            break;
        case GORIGHT:
            x -= speed / FPS;
            break;
        }
        if(x >= this->tgx) {
            x = this->tgx;
            this->status = GOAHEAD;
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
