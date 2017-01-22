#include "carfactory.h"

CarFactory::CarFactory(int x, int y, int gf, int ns, int xs) : Cell(x, y), genFreq(gf), cnt(1), maxSpeed(xs), minSpeed(ns)
{

}

const int CarFactory::getGenFreq() const
{
    return genFreq;
}
