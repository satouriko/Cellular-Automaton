#include "cell.h"

Cell::Cell(int x, int y)  : x(x), y(y)
{
}

const double Cell::getX() const {
    return x;
}

const double Cell::getY() const {
    return y;
}
