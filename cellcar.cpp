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
#include <iostream>

using namespace std;

const double CellCar::getSpeed() const {
    return speed;
}

CellCar::CellCar(int x, int y, Settings &s) : Cell(x, y), status(GOAHEAD), tgx(x), tgy(y), _dir(FORWARD) {
    const int MAXSPEED = 5, MINSPEED = 2;
    speed = rand() % (MAXSPEED + 1 - MINSPEED) + MINSPEED;
    this->SAFEGAP = s.SAFEGAP;
    this->SPEEDLIMIT = s.SPEEDLIMIT;
    this->ACC = s.ACC;
    this->FPS = s.FPS;
}

CellCar::CellCar(int x, int y, double speed, Settings &s) : Cell(x, y), status(GOAHEAD), tgx(x), tgy(y), _dir(FORWARD), speed(speed)
{
    this->SAFEGAP = s.SAFEGAP;
    this->SPEEDLIMIT = s.SPEEDLIMIT;
    this->ACC = s.ACC;
    this->FPS = s.FPS;
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
        //Get Magic block
        char mgc = '3';
        for(vector<CellBlock>::const_iterator iter = cbbegin; iter != cbend; ++iter) {
            if(fabs(iter->getX() - x) < 1 && iter->getY() > y && iter->getY() - y <= 1) {
                mgc = iter->getType();
                break;
            }
        }
        //
        vector<CellCar>::const_iterator fnst = oldend;
        int lcnt = 0, rcnt = 0, mcnt = 0;
        for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
            if(fabs(iter->getX() - x) < 1 && iter->getY() > y) {
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

        //Overtake Problem
        if(fnst != oldend && fnst->getY() - y < SAFEGAP) {
            //speed = fnst->getSpeed();
            if(this->status == GOAHEAD) {
                switch(lineJudge(oldbegin, oldend, cbbegin, cbend, lcnt, rcnt, mcnt, mgc)) {
                case GOLEFT:
                    this->tgx = x + 1;
                    this->status = GOLEFT;
                    return;
                case GORIGHT:
                    this->tgx = x - 1;
                    this->status = GORIGHT;
                    return;
                case WAIT:
                    this->speed = 0;
                    return;
                }
                speed = fnst->getSpeed();
            }
        }
        else
            speed + ACC / FPS >= SPEEDLIMIT ? speed = SPEEDLIMIT : speed += ACC / FPS;
        //Magic Problem Upcase
        if(mgc == 'L' || mgc == 'R' || mgc == '1' || mgc == '2') {
            if(this->status == GOAHEAD) {
                switch (lineJudge(oldbegin, oldend, mgc)) {
                case GOLEFT:
                    this->tgx = x + 1;
                    this->status = GOLEFT;
                    break;
                case GORIGHT:
                    this->tgx = x - 1;
                    this->status = GORIGHT;
                    break;
                case WAIT:
                    this->speed = 0;
                    break;
                }
                return;
            }
        }
        //Magic Problem Lowcase
        if(mgc != '3') {
            if(this->status == GOAHEAD) {
                switch (lineJudge(oldbegin, oldend, mgc)) {
                case GOLEFT:
                    this->tgx = x + 1;
                    this->status = GOLEFT;
                    break;
                case GORIGHT:
                    this->tgx = x - 1;
                    this->status = GORIGHT;
                    break;
                case WAIT:
                    this->speed = 0;
                    break;
                }
            }
        }
    }
        break;

    default :{
    }
        break;
    }
}

// Judge if we should go left or right or keep here while countering magic
RelativeDir CellCar::lineJudge(vector<CellCar>::const_iterator oldbegin, vector<CellCar>::const_iterator oldend,
                               char type)
{
    switch (_dir) {
    case FORWARD: {
        switch(type) {
        case 'L': {
            bool flag1 = false;
            for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
                if(fabs(iter->getX() - (x + 1)) < 1 && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP) {
                    flag1 = true;
                    break;
                }
            }
            if(flag1) return WAIT;
            else return GOLEFT;
        } break;
        case 'R': {
            bool flag2 = false;
            for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
                if(fabs(iter->getX() - (x - 1)) < 1 && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP) {
                    flag2 = true;
                    break;
                }
            }
            if(flag2) return WAIT;
            else return GORIGHT;
        } break;
        case '2': {
            bool flag1 = false, flag2 = false;
            for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
                if(fabs(iter->getX() - (x + 1)) && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP)
                    flag1 = true;
                if(fabs(iter->getX() - (x - 1)) && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP)
                    flag2 = true;
                if(flag1 && flag2) break;
            }
            if(flag1 && flag2) return WAIT;
            else if(flag1) return GORIGHT;
            else if(flag2) return GOLEFT;
            else
                return rand() % 2 ? GOLEFT : GORIGHT;
        } break;
        case '1': {
            return GOAHEAD;
        } break;
        case 'l': {
            bool flag1 = false;
            for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
                if(fabs(iter->getX() - (x + 1)) < 1 && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP) {
                    flag1 = true;
                    break;
                }
            }
            if(flag1) return GOAHEAD;
            else return GOLEFT;
        } break;
        case 'r': {
            bool flag2 = false;
            for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
                if(fabs(iter->getX() - (x - 1)) < 1 && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP) {
                    flag2 = true;
                    break;
                }
            }
            if(flag2) return GOAHEAD;
            else return GORIGHT;
        } break;
        }

            }
    default:
        return GOAHEAD;
    }
}

// Judge if we should go left or right or keep here while overtaking
RelativeDir CellCar::lineJudge(vector<CellCar>::const_iterator oldbegin, vector<CellCar>::const_iterator oldend,
                               vector<CellBlock>::const_iterator cbbegin, vector<CellBlock>::const_iterator cbend,
                               int lcnt, int rcnt, int mcnt, char mgc)
{
    switch (_dir) {
    case FORWARD: {
        bool flag1 = false, flag2 = false;
        for(vector<CellCar>::const_iterator iter = oldbegin; iter != oldend; ++iter) {
            if(fabs(iter->getX() - (x + 1)) < 1 && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP)
                flag1 = true;
            if(fabs(iter->getX() - (x - 1)) < 1 && fabs(iter->getY() + iter->getSpeed() - y - speed )  < SAFEGAP)
                flag2 = true;
            if(flag1 && flag2) break;
        }
        if(!(flag1 && flag2)) {
            for(vector<CellBlock>::const_iterator iter = cbbegin; iter != cbend; ++iter) {
                if(iter->getType() == 'R' && fabs(iter->getX() - (x + 1)) < 1 && fabs(iter->getY() - y - 1)  < 1)
                    flag1 = true;
                if(iter->getType() == 'L' && fabs(iter->getX() - (x - 1)) < 1 && fabs(iter->getY() - y - 1)  < 1)
                    flag2 = true;
                if(flag1 && flag2) break;
            }
        }
        if(flag1 && flag2) return GOAHEAD;
        else if(flag1) {
            if(mgc == '3') return GORIGHT;
            else return GOAHEAD;
        }
        else if(flag2) {
            if(mgc == '3') return GOLEFT;
            else return GOAHEAD;
        }
        else
            return lcnt < rcnt ? ( lcnt < mcnt ? ( mgc == '3' ? GOLEFT : GOAHEAD ) : GOAHEAD ) : ( rcnt < mcnt ? ( mgc == '3' ? GORIGHT : GOAHEAD ) : GOAHEAD );
    }
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
            if(x >= this->tgx) {
                x = this->tgx;
                this->status = GOAHEAD;
            }
            break;
        case GORIGHT:
            x -= speed / FPS;
            if(x <= this->tgx) {
                x = this->tgx;
                this->status = GOAHEAD;
            }
            break;
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
