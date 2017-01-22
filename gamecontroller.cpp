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

void GameController::clearCarFactories()
{
    this->cfs.clear();
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
    this->dh.drawCarFactories(this->cfs);
}

void GameController::carFactory()
{
    for(vector<CarFactory>::iterator iter = cfs.begin(); iter != cfs.end(); ++iter) {
        if(iter->cnt++ % (FPS / iter->genFreq) == 0) {
            if(rand() % 2) {
                double speed = rand() % (iter->maxSpeed + 1 - iter->minSpeed) + iter->minSpeed;
                CellCar c(iter->getX(), iter->getY(), speed, this->settings);
                this->stage.push_back(c);
            }
            iter->cnt = 1;
        }
    }
}

void GameController::blockFactory(int x, int y, char type)
{
    CellBlock cb(x, y, type);
    this->edge.push_back(cb);
}

void GameController::cfFactory(int x, int y, int gf, int minSpeed, int maxSpeed)
{
    CarFactory cf(x, y, gf, minSpeed, maxSpeed);
    this->cfs.push_back(cf);
}
