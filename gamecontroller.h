//
// Created by lijiahao on 9/10/16.
//

#ifndef CA_GAMECONTROLLER_H
#define CA_GAMECONTROLLER_H

#include "cellcar.h"
#include "carfactory.h"
#include "drawhelper.h"
#include "settings.h"
#include <vector>
#include <QPainter>
#include <QWidget>

#define LEFTXLIM 0
#define RIGHTXLIM 8 //Exclude
#define TOPYLIM 0
#define BOTTOMYLIM 30 //Exclude
/***************/
//#define FPS 50
/***************/
#define GENFREQ 1 //Num of waves car factory produce per second

//ACC has an effect on time. So that it's not strange that speed correlate to FPS
//High FPS causes splash screen

class GameController : public QWidget
{
    Q_OBJECT
public:
    GameController(Settings &s);
    int FPS;
    void startLooping();
    void stopLooping();
    void clearBlock();
    void clearCar();
    void clearCarFactories();
    void updateParams();

public slots:
    void draw(QPainter *painter);
    void loop();
    void blockFactory(int x, int y, char type);
    void cfFactory(int x, int y, int gf, int minSpeed, int maxSpeed);
signals:
    void onRedraw();
private:
    DrawHelper dh;
    std::vector<CellCar> stage;
    std::vector<CellBlock> edge;
    std::vector<CarFactory> cfs;
    void carFactory();
    QTimer *timer;
    Settings &settings;
};
#endif //CA_GAMECONTROLLER_H
