//
// Created by lijiahao on 9/10/16.
//

#include "CellCar.h"
#include "GameController.h"
#include "drawhelper.h"
#include <random>
#include <algorithm>
#include <QTimer>
#include <iostream>

using namespace std;

GameController::GameController() {}

void GameController::startLooping() {
    QTimer *timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT( loop() ) );
    timer->start(1000);
}

void GameController::loop()
{
    emit onRedraw();
    for (vector<CellCar>::iterator iter = this->stage.begin(); iter != this->stage.end(); ++iter) {
        if(iter->getY() > BOTTOMYLIM)
            iter = stage.erase(iter);
        iter->moveOn(this->stage.begin(), this->stage.end());
    }
    carFactory();

}

void GameController::draw(QPainter *painter) {
    this->dh.syncPainter(painter);
    this->dh.clc();
    this->dh.drawCars(this->stage);
}

void GameController::carFactory()
{
    for(int i = LEFTXLIM; i < RIGHTXLIM; ++i) {
        if(rand() % 2) {
            CellCar *c = new CellCar(i, TOPYLIM);
            this->stage.push_back(*c);
        }
    }
}
