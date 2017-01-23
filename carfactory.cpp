#include "carfactory.h"

CarFactory::CarFactory(int x, int y, double gf, int ns, int xs) : Cell(x, y), genFreq(gf), cnt(1), maxSpeed(xs), minSpeed(ns)
{

}

const double CarFactory::getGenFreq() const
{
    return genFreq;
}
