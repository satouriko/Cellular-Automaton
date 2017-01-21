#ifndef CELLBLOCK_H
#define CELLBLOCK_H

#include "cell.h"

class CellBlock : public Cell
{
public:
    CellBlock(int x, int y, char t);
    const char getType() const ;
private:
    char type;
};

#endif // CELLBLOCK_H
