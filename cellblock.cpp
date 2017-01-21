#include "cellblock.h"

CellBlock::CellBlock(int x, int y, char t) : Cell(x, y), type(t)
{

}

const char CellBlock::getType() const
{
    return type;
}
