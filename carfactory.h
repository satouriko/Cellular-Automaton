#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "cell.h"

class GameController;

class CarFactory : public Cell
{
public:
    CarFactory(int x, int y, int gf, int ns, int xs);
    const int getGenFreq() const;
    friend class GameController;
private:
    int genFreq;
    int cnt;
    int minSpeed;
    int maxSpeed;
};

#endif // CARFACTORY_H
