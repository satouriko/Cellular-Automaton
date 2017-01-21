#ifndef CELL_H
#define CELL_H


class Cell
{
protected:
    Cell(int x, int y);
    double x, y;
public:
    const double getX() const ;
    const double getY() const ;
};

#endif // CELL_H
