#ifndef CARFACTORY_H
#define CARFACTORY_H

#include "cell.h"

class GameController;

class CarFactory : public Cell
{
public:
    CarFactory(int x, int y, double gf, int ns, int xs);
    const double getGenFreq() const;
    friend class GameController;
private:
    double genFreq;
    int cnt;
    int minSpeed;
    int maxSpeed;
};

#endif // CARFACTORY_H
