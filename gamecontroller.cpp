//
// Created by lijiahao on 9/10/16.
//

#include "cellcar.h"
#include "cellblock.h"
#include "gamecontroller.h"
#include "drawhelper.h"
#include <random>
#include <algorithm>
#include <QTimer>
#include <iostream>

using namespace std;

GameController::GameController(Settings &s) : settings(s)
{
    this->timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT( loop() ) );
    this->FPS = s.FPS;
}

void GameController::startLooping() {
    //blockFactory();
    timer->start(1000 / FPS);
}

void GameController::stopLooping()
{
    timer->stop();
}

void GameController::clearBlock()
{
    this->edge.clear();
}

void GameController::clearCar()
{
    this->stage.clear();
}

void GameController::updateParams()
{
    this->FPS = settings.FPS;
    this->timer->setInterval(1000 / this->FPS);
    for(auto it = this->stage.begin(); it != this->stage.end(); ++it)
    {
        it->SAFEGAP = this->settings.SAFEGAP;
        it->SPEEDLIMIT = this->settings.SPEEDLIMIT;
        it->ACC = this->settings.ACC;
        it->FPS = this->settings.FPS;
    }
}

void GameController::loop()
{
    emit onRedraw();
    vector<CellCar> temp(stage.begin(), stage.end());
    for (vector<CellCar>::iterator iter = this->stage.begin(); iter != this->stage.end(); ++iter) {
        if(iter->getY() > BOTTOMYLIM)
            iter = stage.erase(iter);
        iter->moveOn(temp.begin(), temp.end(), this->edge.begin(), this->edge.end());
    }
    carFactory();

}

void GameController::draw(QPainter *painter) {
    this->dh.syncPainter(painter);
    this->dh.clc();
    this->dh.drawBlocks(this->edge);
    this->dh.drawCars(this->stage);
}

void GameController::carFactory()
{
    static int cnt = 1;
    if(cnt++ % (FPS / GENFREQ) == 0) {
        for(int i = LEFTXLIM; i < RIGHTXLIM; ++i) {
            if(rand() % 2) {
                CellCar c(i, TOPYLIM, this->settings);
                this->stage.push_back(c);
            }
        }
        cnt = 1;
    }
}

void GameController::blockFactory()
{
    for(auto i = 0; i <= 30; ++i) {
        this->edge.push_back(*(new CellBlock(0, i, 'L')));
        this->edge.push_back(*(new CellBlock(7, i, 'R')));
    }
    for(auto i = 5; i <= 30; ++i) {
        this->edge.push_back(*(new CellBlock(1, i, 'L')));
    }
    for(auto i = 8; i <= 30; ++i) {
        this->edge.push_back(*(new CellBlock(2, i, 'L')));
    }
    for(auto i = 11; i <= 30; ++i) {
        this->edge.push_back(*(new CellBlock(3, i, 'L')));
    }
    for(auto i = 1; i <= 4; ++i) {
        this->edge.push_back(*(new CellBlock(i, 5, 'L')));
    }
    for(auto i = 2; i <= 4; ++i) {
        this->edge.push_back(*(new CellBlock(i, 8, 'L')));
    }
    for(auto i = 3; i <= 4; ++i) {
        this->edge.push_back(*(new CellBlock(i, 11, 'L')));
    }
}

void GameController::blockFactory(int x, int y, char type)
{
    CellBlock cb(x, y, type);
    this->edge.push_back(cb);
}
